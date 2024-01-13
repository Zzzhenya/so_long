#include <stdio.h>
#include <mlx.h>
#include <stdlib.h>
#include <string.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_cord {
	int 	x;
	int 	y;
	char 	val;
} t_cord;

typedef struct s_map {
	int 	height;
	int 	width;
	t_cord 	*game;
}	t_map;

int	close(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void print_map(t_map *map)
{
	int i;
	i = 0;

	while(i < map->width * map->height)
	{
		printf("%c ", map->game[i].val);
		if (!(i % map->width))
			printf("\n");
		i ++;
	} 
}

int mlx(t_map *map)
{
	t_vars vars;
	t_data 	img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 500, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 800, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	print_map(map);
	my_mlx_pixel_put(&img, 100, 100, 0x00FFFFFF);
	my_mlx_pixel_put(&img, 200, 100, 0x00FFFFFF);
	my_mlx_pixel_put(&img, 200, 200, 0x00FFFFFF);
	my_mlx_pixel_put(&img, 100, 200, 0x00FFFFFF);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, close, &vars);
	mlx_loop(vars.mlx);
	printf("MLX Closed.\n");
	mlx_destroy_window(vars.mlx, vars.win);
	return (0);
}

int get_map_from_file(char *filename, t_map *map)
{
	FILE	*fp;
	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;

	map->height = 0;
	fp = fopen(filename, "r");
	while ((linelen = getline(&line, &linecap, fp)) > 0)
	{
		map->height ++;
		map->width = strlen(line);
	}
	fclose(fp);
	return (0);
}

void store_map(char *name, t_map *map)
{
	FILE	*fp;
	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;
	int i = 0;
	int j = 0;

	fp = fopen(name, "r");
	while ((linelen = getline(&line, &linecap, fp)) > 0)
	{
		j = 0;
		while (j < map->width)
		{
			map->game[map->width * i + j].val = line[j];
			map->game[map->width * i + j].x = j;
			map->game[map->width * i + j].y = i;
			j ++;
		}
		i ++;
	}
	fclose(fp);
}

int main(int argc, char **argv)
{
	t_map map;

	if (argc != 2)
	{
		printf("We need a map to run!\n");
		return (0);
	}
	get_map_from_file(argv[1], &map);
	map.game = malloc(sizeof(t_cord) * map.height * map.width);
	store_map(argv[1], &map);
	mlx(&map);
	return (0);
}