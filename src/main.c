#include "RTv1.h"

int main()
{
	t_app	*app;

	app = (t_app *)malloc(sizeof(t_app));
    app->sdl = (t_sdl *)malloc(sizeof(t_sdl));
	init_app(app);
	start_the_game2(app);

	return 0;
}