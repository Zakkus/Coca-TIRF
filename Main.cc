#include "Main.hh"

int main(int argc, char* argv[])
{
    SDL_Surface* image = loadImage(argv[1]);
    SDL_Surface* final_image = loadImage(argv[1]);
    SDL_Surface* white_image = loadImage(argv[1]);

	tbb::task_scheduler_init init;

    redFilter(image);


    dilate(image,2,0);
    erode(image, 0,4);
    dilate(image, 0,4);
    erode(image, 4,0);
    dilate(image, 4,0);
    erode(image, 3,3);
    dilate(image, 3,3);

    dilate(image,5,0);
    erode(image,5,0);

    Compo(image);
    int i = 0;
    bool done = false;
    std::vector<std::tuple<int,std::pair<float,float>, int,int,int,int> > percents;
    std::map<int, int> compos = ChooseCompo(image);
	tbb::parallel_for(tbb::blocked_range<int>(0,5), par_1(image, white_image, &compos, &percents));
   

	tbb::parallel_for(tbb::blocked_range<int>(0, percents.size()), par_2(final_image, &done, &percents));



     for (i = 0; i < percents.size(); i++)
       if (std::get<2>(percents[i]) == 0)
           percents.erase(percents.begin()+i);


    if (!done && !percents.empty())
    {
        std::sort(begin(percents), end(percents),
                [](std::tuple<int,std::pair<float,float>,int,int,int,int> const &t1,
                   std::tuple<int,std::pair<float,float>,int,int,int,int> const &t2)
                {
                    return std::abs(std::get<2>(t1) - 60) >
                           std::abs(std::get<2>(t2) - 60);
                });

        std::pair<float,float> white = std::get<1>(percents[0]);
        int proportion = std::get<0>(percents[0]);
        int L = std::get<2>(percents[0]), l = std::get<3>(percents[0]);
        int min_left = std::get<4>(percents[0]), min_up = std::get<5>(percents[0]);
        if (proportion <= 85 && proportion >= 51)
            draw_rectangle(final_image, L, l, min_left, min_up);
    }


    SDL_Window* window = createWindow();
    if (window == NULL)
        return 1;
    displayImage(window, final_image);
    SDL_Delay(5000);

    return 0;
}
