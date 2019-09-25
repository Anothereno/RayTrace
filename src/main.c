#include "RTv1.h"

int main()
{
	t_app	*app;

	app = (t_app *)malloc(sizeof(t_app));
    app->sdl = (t_sdl *)malloc(sizeof(t_sdl));
	//bzero(app, sizeof(t_app));
	init_app(app);
	start_the_game(app);

	return 0;
}