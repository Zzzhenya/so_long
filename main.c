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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int mlx(void)
{
	void	*mlx = NULL;
	void	*mlx_win = NULL;
	t_data 	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 500, "Hello world!");
	img.img = mlx_new_image(mlx, 800, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	my_mlx_pixel_put(&img, 100, 100, 0x00FFFFFF);
	my_mlx_pixel_put(&img, 200, 100, 0x00FFFFFF);
	my_mlx_pixel_put(&img, 200, 200, 0x00FFFFFF);
	my_mlx_pixel_put(&img, 100, 200, 0x00FFFFFF);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	
	mlx_loop(mlx);
	printf("MLX Closed.\n");
	free(mlx_win);
	return (0);
}

int main(void)
{
	mlx();
	return (0);
}