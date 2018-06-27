#define _USE_MATH_DEFINES 
#include <iostream>
#include "Point.hpp"
#include <vector>
#include <time.h>
#include <algorithm>
#include <math.h>

int main()
{
	int number;
	std::cout << "Please enter the number of points you want to generate: ";
	std::cin >> number;
	int modulo = 10;
	std::cout << "Please specify the range for the generated points (i. e. 10 -> 0,1,...,9): ";
	std::cin >> modulo;
	std::vector<Point*> points;
	srand(time(NULL));
	
	for (int i = 0; i < number; ++i) {
		points.push_back(new Point{rand()% modulo,rand()% modulo });
	}

	std::sort(points.begin(), points.end(), [](Point* const& a, Point* const& b) { return a->y < b->y; });

	for (int i = 0; i < number - 1; ++i) {
		auto x = points.at(i + 1)->x - points.at(0)->x;
		auto y = points.at(i + 1)->y - points.at(0)->y;
		auto x2 = points.at(i + 1)->x - points.at(0)->x;
		auto y2 = 0;
		auto length_x_y = sqrt(pow(x, 2) + pow(y, 2));
		auto length_x2_y2 = sqrt(pow(x2, 2) + pow(y2, 2));
		auto alpha = acos( length_x2_y2 / length_x_y) * (180/M_PI);
		if (x > 0) {
			points.at(i + 1)->angle = alpha;
		}
		else {
			points.at(i + 1)->angle = 180 - alpha;
		}
	}

	std::sort(points.begin(), points.end(), [](Point* const& a, Point* const& b) { return a->angle < b->angle; });

	for (int i = 0; i < number - 1; ++i) {
		points.at(i)->next_Pointer = points.at(i + 1);
	}
	points.at(number - 1)->next_Pointer = points.at(0);

	bool finished = false;
	Point* start = points.at(0);
	Point* tmp = start;
	
	std::cout << "Closed Path: \n";
	std::cout << "Punkt 1 (" << start->x << " , " << start->y << ")\n";
	int i = 1;
	while (!finished) {
		tmp = tmp->next_Pointer;
		if (tmp == start) {
			finished = true;
		} else {
			i += 1;
			std::cout << "Punkt "<< i<< " (" << tmp->x << " , " << tmp->y << ")\n";
		}
	}
	std::cout << "--------------------------------------------------------------\n";
	std::cout << "Angels inbetween: \n";
	for (int i = 0; i < points.size(); ++i) {
			double angle_1;
			double angle_2;
			int prev = i - 1;
			int next = i + 1;
			int base = 0;

			if (i == 0) {
				prev = points.size() - 1;
				next = 1;
				base = 2;
			} else if (i == points.size() - 1) {
				prev = points.size() - 2;
				next = 0;
				base = 1;
			}

			auto x = points.at(i)->x - points.at(base)->x;
			auto y = points.at(i)->y - points.at(base)->y;
			auto x2 = points.at(i)->x - points.at(prev)->x;
			auto y2 = points.at(i)->y - points.at(prev)->y;
			auto x3 = points.at(prev)->x - points.at(base)->x;
			auto y3 = points.at(prev)->y - points.at(base)->y;
			auto x4 = points.at(i)->x - points.at(next)->x;
			auto y4 = points.at(i)->y - points.at(next)->y;
			auto x5 = points.at(next)->x - points.at(base)->x;
			auto y5 = points.at(next)->y - points.at(base)->y;

			auto x_y = pow(x, 2) + pow(y, 2);
			auto x2_y2 = pow(x2, 2) + pow(y2, 2);
			auto x3_y3 = pow(x3, 2) + pow(y3, 2);
			auto x4_y4 = pow(x4, 2) + pow(y4, 2);
			auto x5_y5 = pow(x5, 2) + pow(y5, 2);
			angle_1 = acos((x_y + x2_y2 - x3_y3) / (2 * sqrt(x_y)*sqrt(x2_y2))) * (180 / M_PI);
			angle_2 = acos((x_y + x4_y4 - x5_y5) / (2 * sqrt(x_y)*sqrt(x4_y4))) * (180 / M_PI);
			auto alpha = angle_1 + angle_2;
			points.at(i)->angle_between = alpha;
			if (alpha > 180) {
				points.erase(points.begin() + i);
				points.at(i - 1)->next_Pointer = points.at(i);
				i = i - 2;
			}
			std::cout << alpha << "\n";
	}

	std::cout << "--------------------------------------------------------------\n";
	finished = false;
	start = points.at(0);
	tmp = start;

	std::cout << "Convex Hull: \n";
	std::cout << "Punkt 1 (" << start->x << " , " << start->y << ")\n";
	i = 1;
	while (!finished) {
		tmp = tmp->next_Pointer;
		if (tmp == start) {
			finished = true;
		}
		else {
			i += 1;
			std::cout << "Punkt " << i << " (" << tmp->x << " , " << tmp->y << ")\n";
		}
	}















	std::cout << "Angels inbetween: \n";
	for (int i = 0; i < points.size(); ++i) {
		double angle_1;
		double angle_2;
		int prev = i - 1;
		int next = i + 1;
		int base = 0;

		if (i == 0) {
			prev = points.size() - 1;
			next = 1;
			base = 2;
		}
		else if (i == points.size() - 1) {
			prev = points.size() - 2;
			next = 0;
			base = 1;
		}

		auto x = points.at(i)->x - points.at(base)->x;
		auto y = points.at(i)->y - points.at(base)->y;
		auto x2 = points.at(i)->x - points.at(prev)->x;
		auto y2 = points.at(i)->y - points.at(prev)->y;
		auto x3 = points.at(prev)->x - points.at(base)->x;
		auto y3 = points.at(prev)->y - points.at(base)->y;
		auto x4 = points.at(i)->x - points.at(next)->x;
		auto y4 = points.at(i)->y - points.at(next)->y;
		auto x5 = points.at(next)->x - points.at(base)->x;
		auto y5 = points.at(next)->y - points.at(base)->y;

		auto x_y = pow(x, 2) + pow(y, 2);
		auto x2_y2 = pow(x2, 2) + pow(y2, 2);
		auto x3_y3 = pow(x3, 2) + pow(y3, 2);
		auto x4_y4 = pow(x4, 2) + pow(y4, 2);
		auto x5_y5 = pow(x5, 2) + pow(y5, 2);
		angle_1 = acos((x_y + x2_y2 - x3_y3) / (2 * sqrt(x_y)*sqrt(x2_y2))) * (180 / M_PI);
		angle_2 = acos((x_y + x4_y4 - x5_y5) / (2 * sqrt(x_y)*sqrt(x4_y4))) * (180 / M_PI);
		auto alpha = angle_1 + angle_2;
		points.at(i)->angle_between = alpha;
		std::cout << alpha << "\n";
	}















	std::cin.get();
	std::cin.get();
	return 0;
}
