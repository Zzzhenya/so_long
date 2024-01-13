#include <stdio.h>
#include <mlx.h>
#include <stdlib.h>

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

int mlx(void)
{
	t_vars vars;
	t_data 	img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 500, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 800, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
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

int main(void)
{
	mlx();
	return (0);
}