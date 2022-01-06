#include "SDL.h"
#include"Windows.h"

int real = 800;
int imag = 800;

int inset(double a, double b, double scalet) {
	scalet *= 250;
	double ox = real / 2;
	double oy = imag / 2;
	double x = 0;
	double x1 = (a - ox) /scalet - scalet*0.1/250;
	double y = 0;
	double y1 = (oy - b) /scalet + scalet*0.15/250;
	double max_iteration = 255;
	int i = 0;
	if (x1 * x1 + y1 * y1 <= 4)
		while (x * x + y * y <= 4 && i < max_iteration) {
			double xtemp = x * x - y * y + x1;
			y = 2 * x * y + y1;
			x = xtemp;
			i++;
		}
	return i;
}

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(1440, 900, 0, &window, &renderer);
	SDL_RenderSetLogicalSize(renderer, real, imag);

	/*int count = 0;*/
	double scale = 1;

	while (1) {
		SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
			return 0;
		}
		if (GetKeyState('Q') & 0x8000) {
			return 0;
		}

		for (int x = 0; x < real; x++) {

			for (int y = 0; y < imag; y++) {

				int color = inset(x, y, scale);

				int red = 2*color%255;
				int green = 5 * color % 255;
				int blue = 7 * color % 255;
				SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}
		scale += 0.05;
	}


	return 0;
}