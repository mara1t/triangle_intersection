
#include "..//include//triangle_t.h"

#include <iostream>
#include <stdio.h>
#include <list>
#include <vector>


triangles::point_t get_pt()
{
    double x = 0, y = 0, z = 0;
    std::cin >> x >> y >> z;

    triangles::point_t tmp_pt{x, y, z};
    return tmp_pt;
}

int triag_inters(const int n) {
    std::list<std::pair<triangles::triangle_t, int>> notcrossing_tr;
    std::vector<std::pair<triangles::triangle_t, int>> crossing_tr;

    for (int id = 0; id < n; id++) {
        triangles::point_t pt1 = get_pt();
        triangles::point_t pt2 = get_pt();
        triangles::point_t pt3 = get_pt();

        triangles::triangle_t triag{pt1, pt2, pt3};
        std::pair<triangles::triangle_t, int> newPr = std::make_pair(triag, id);

        bool fl = false;
        for (auto lstIter = notcrossing_tr.begin(); lstIter != notcrossing_tr.end(); ) {
            std::pair<triangles::triangle_t, int> pair = *lstIter;
            if (pair.first.all_intersection(triag)) {
                std::cout << pair.second << " ";
                fl = true;

                lstIter = notcrossing_tr.erase(lstIter);
                crossing_tr.push_back(pair);
            }
            else  
                ++lstIter;
        }

        if (fl) {
            std::cout << id << " ";
            crossing_tr.push_back(newPr);
            continue;
        }

        auto vecIter = crossing_tr.begin();
        for (; vecIter != crossing_tr.end(); ++vecIter) {
            std::pair<triangles::triangle_t, int> pr = *vecIter;
            if (pr.first.all_intersection(triag)) {
                std::cout << id << " ";

                crossing_tr.push_back(newPr);

                break;
            }
        }
        //std::cout << "here\n";
        if (vecIter == crossing_tr.end())
            notcrossing_tr.push_back(newPr);
    }
    std::cout << std::endl;
    return 0;
}

int main()
{
    triag_inters(2);
    return 0;
}