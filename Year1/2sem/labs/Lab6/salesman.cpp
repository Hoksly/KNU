#include "salesman.hpp"

double ALPHA = 3;
double BETA = 1.8;

double FEROMON_PER_ANT = 100;
double EVOPARTION_CONST = 0.8;
double INIT_FEROMON = 0.2;
int GENERATIONS = 1500;
int ANTS_NUMBER = 500;

uchar **gather(Ant *mas)
{
    uchar **ret = new uchar *[ANTS_NUMBER];
    for (int i = 0; i < ANTS_NUMBER; ++i)
        ret[i] = mas[i].Path;

    return ret;
}

inline void print_res(uchar *mas, uchar n)
{
    for (uchar i = 0; i < n; ++i)
        std::cout << mas[i] << ' ';
    std::cout << std::endl;
}

uchar *run(Ant *Ants, AntMap &Map, uchar n, bool print = true)
{
    uchar cur, **Pathes;
    Pathes = gather(Ants);
    for (int i = 0; i < GENERATIONS; ++i)
    {
        if (print)
            std::cout << "GENERATION: " << i << '\n';
        cur = rand() % n;
        for (int i = 0; i < ANTS_NUMBER; ++i)
        {
            Ants[i].move(cur, Map);
        }

        Map.recalculate_feromon(Pathes, ANTS_NUMBER);
    }

    // print_res(Ants[0].give_shortest(0, Map), n + 1);
    return Ants[0].give_shortest(0, Map);
}

std::vector<std::pair<std::pair<double, double>, int>> test(Ant *Ants, AntMap &Map, uchar n)
{
    std::cout << '\n'
              << '\n';
    std::vector<std::pair<std::pair<double, double>, int>> V;

    for (ALPHA = 0; ALPHA < 20; ALPHA += 0.3)
    {
        for (BETA = 0; BETA < 20; BETA += 0.3)
        {
            std::pair<std::pair<double, double>, int> pr = std::make_pair(std::make_pair(ALPHA, BETA), Map.calculate_path(run(Ants, Map, n, true), n + 1));
            std::cout << pr.first.first << ' ' << pr.first.second << ' ' << pr.second << '\n';
            V.push_back(pr);
        }
    }
    return V;
}

double GiveLen(double alpha, double beta, AntMap &Map, int generations, int ant_n, double evap_const, double init_fer, double fer_per_ant)
{
    // Not a great way to do it, but let it be...
    ALPHA = alpha;
    BETA = beta;
    GENERATIONS = generations;
    ANTS_NUMBER = ant_n;
    EVOPARTION_CONST = evap_const;
    INIT_FEROMON = init_fer;
    FEROMON_PER_ANT = fer_per_ant;

    Ant Ants[ANTS_NUMBER];

    for (int i = 0; i < ANTS_NUMBER; ++i)
        Ants[i].update(Map.n);

    uchar **Pathes;
    Pathes = gather(Ants);

    return Map.calculate_path(run(Ants, Map, Map.n, true), Map.n + 1);
}

int main(int argc, char **argv)
{

    int **Matrix;
    uchar n, cur, **Pathes, *res;

    if (argc > 1)
    {
        if (search_key("-h", argc, argv))
        {
            display_help();
            return 0;
        }

        if (search_key("-c", argc, argv))
        {

            std::cin >> n;
            Matrix = input(n);
        }
        else
        {

            char *filename = search_value("-f", argc, argv);
            if (filename)
            {
                Matrix = file_input(n, filename);
            }
            else
            {
                display_help();
                return 1;
            }

            char *alpha, *beta, *fer_per_ant, *evap_const, *gen_con, *ants_num, *init_fer;

            alpha = search_value("-p", argc, argv);
            fer_per_ant = search_value("-r", argc, argv);
            evap_const = search_value("-e", argc, argv);
            gen_con = search_value("-g", argc, argv);
            ants_num = search_value("-a", argc, argv);
            init_fer = search_value("-i", argc, argv);

            if (alpha)
            {
                try
                {
                    ALPHA = std::stod(alpha);
                    BETA = std::stod(alpha + 1);
                }
                catch (...)
                {
                    display_help();
                    return 1;
                }
            }

            if (fer_per_ant)
            {
                try
                {
                    FEROMON_PER_ANT = std::stod(fer_per_ant);
                }
                catch (...)
                {
                    display_help();
                    return 1;
                }
            }

            if (evap_const)
            {
                try
                {
                    EVOPARTION_CONST = std::stod(evap_const);
                }
                catch (...)
                {
                    display_help();
                    return 1;
                }
            }

            if (gen_con)
            {
                try
                {
                    GENERATIONS = std::stoi(gen_con);
                }
                catch (...)
                {
                    display_help();
                    return 1;
                }
            }

            if (ants_num)
            {
                try
                {
                    ANTS_NUMBER = std::stoi(ants_num);
                }
                catch (...)
                {
                    display_help();
                    return 1;
                }
            }
            if (init_fer)
            {
                try
                {
                    INIT_FEROMON = std::stod(ants_num);
                }
                catch (...)
                {
                    display_help();
                    return 1;
                }
            }
        }
    }
    else
    {
        display_help();
        return 0;
    }
    bool silent = (bool)search_key("-s", argc, argv);

    AntMap Map(n, Matrix);

    Ant Ants[ANTS_NUMBER];

    for (int i = 0; i < ANTS_NUMBER; ++i)
        Ants[i].update(n);

    uchar *path = run(Ants, Map, Map.n, !silent); // aray of vertices
    std::cout << "Total length: " << Map.calculate_path(path, Map.n) << std::endl;
    std::cout << "Path: ";
    for (uchar i = 0; i < n; ++i)
        std::cout << path[i] << ' ';
    std::cout << std::endl;
}