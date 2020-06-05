#include <fstream>
#include <iostream>
#include <string>
#include "Route.h"
#include "Market.h"
#include <locale.h>
#include "StoreHouse.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Texture.hpp>

using namespace std;
using namespace sf;

int main(){

ifstream in;
setlocale(LC_ALL, "Russian");
char ch = 0;
int n=0, m=0;

in.open("Map.txt");
while (ch != -1) {
    ch = (char) in.get();
    if (ch == '0') {
        m++;
    } else if(ch == '1'){
        m++;
    } else if (ch == '2') {
        m++;
    } else if (ch == '3') {
        m++;
    }
    if (ch == '\n') {
			n++;
		}
	}
in.close();
m = m / n;
int** chart = new int* [n];
for (int i = 0; i < n; i++)
{
    chart[i] = new int[m];
}
in.open("Map.txt");
for (int i = 0; i < n;i++)
{
    for (int j = 0; j < m; j++)
    {
        in >> chart[i][j];
    }
}
in.close();
int stc = 0, shc = 0;
for (int i = 0; i < n; i++)
{
    for (int j = 0; j < m; j++)
		{
			if (chart[i][j] == 3) {
				stc++;
			}
			if (chart[i][j] == 2) {
				shc++;
			}
			if(chart[i][j] == 3 && chart[i+1][j] == 1 && chart[i-1][j] == 1 && chart[i][j+1] == 1 && chart[i][j-1] == 1)
			{
				cout << "Error when entering the card" << endl;return 0;
			} else if (chart[i][j] == 2 && chart[i + 1][j] == 1 && chart[i - 1][j] == 1 && chart[i][j + 1] == 1 && chart[i][j - 1] == 1)
			{
				cout << "Error when entering the card" << endl;return 0;
			}
		}
}
if (stc > 1) {
    cout << "Error when entering the card" << endl;
    return 0;
} else if (stc == 0) {
    cout << "Error when entering the card" << endl;
    return 0;
}
if (shc == 0)
{
    cout << "Error when entering the card" << endl;
    return 0;
}
Route Route;
for (int i = 0; i < n; i++)
{
    for (int j = 0; j < m; j++)
    {
        if (chart[i][j] == 2)
        {
            Market Market(i, j);
            Route.setMarket(Market);
        } else if (chart[i][j] == 3)
        {
            StoreHouse store(i, j);
            Route.setStore(store);
        }
    }
}
vector<Node> tN;
tN.push_back(Route.store);
for (Market i : Route.wh)
{
    tN.push_back(i);
}
int iter = tN.size();
Node b, e;
for (int i = 0; i < iter;i++) {
    Way Way;
    if (i==0) {
        b = tN[0];
        Way.setbg(b);
        float min = Route.shrtWay(b, tN[1]);
        for (int j = 1; j < tN.size(); j++) {
            if (Route.shrtWay(b, tN[j]) < min) {
                min = Route.shrtWay(b, tN[j]);
            }
        }
        for (int j = 1; j < tN.size(); j++) {
            if (Route.shrtWay(b, tN[j]) == min) {
                Way.setEnd(tN[j]);
                b = tN[j];
                tN.erase(tN.begin() + j);
                break;
            }
        }
    } else if(i == iter-1){
			Way.setbg(b);
			e = tN.back();
			Way.setEnd(e);
		} else {
			Way.setbg(b);
			float min = Route.shrtWay(b, tN[iter-i-1]);
			for (int j = 1; j < iter - i; j++) {
				if (Route.shrtWay(b, tN[j]) < min) {
					min = Route.shrtWay(b, tN[j]);
				}
			}
			for (int j = 1; j < iter - i; j++) {
				if (Route.shrtWay(b, tN[j]) == min) {
					Way.setEnd(tN[j]);
					b = tN[j];
					tN.erase(tN.begin() + j);
					break;
				}
			}
		}
		Route.setWay(Way);
	}
int counter = 0;
for (Way l : Route.Ways) {
    int j1 = l.bg.i, j2 = l.bg.j;

    while ((j1 != l.end.i) || (j2 != l.end.j)){

        if (j1 < l.end.i) {
            if (counter > m * n) {
                break;
            }
            if (chart[j1 + 1][j2] != 1) {
                j1++;
                chart[j1][j2] = 4;
                counter++;
                if ((j1 == l.end.i) && (j2 == l.end.j)) {
                    chart[j1][j2] = 5;
                    break;
                }
                continue;
            } else if (chart[j1][j2 + 1] != 1) {
                j2++;
                chart[j1][j2] = 4;
                counter++;
                if ((j1 == l.end.i) && (j2 == l.end.j)) {
                    chart[j1][j2] = 5;
                    break;
					}
                if (chart[j1 + 1][j2] != 1) {
                    j1++;
                    chart[j1][j2] = 4;
                    counter++;
                    if ((j1 == l.end.i) && (j2 == l.end.j)) {
                        chart[j1][j2] = 5;
                        break;
                    }
                    continue;
                }
                continue;
            } else if (chart[j1 - 1][j2] != 1) {
                j1--;
                chart[j1][j2] = 4;
                counter++;
                if ((j1 == l.end.i) && (j2 == l.end.j)) {
                    chart[j1][j2] = 5;
                    break;
                }
                continue;
            } else if (chart[j1][j2-1] != 1) {
                j2--;
                chart[j1][j2] = 4;
                counter++;
                if ((j1 == l.end.i) && (j2 == l.end.j)) {
                    chart[j1][j2] = 5;
                    break;
                }
                continue;
            }
        }
        if (j2 < l.end.j) {
            if (counter > m * n) {
					break;
            }
            if (chart[j1][j2 + 1] != 1) {
                j2++;
                chart[j1][j2] = 4;
                counter++;
                if ((j1 == l.end.i) && (j2 == l.end.j)) {
                    chart[j1][j2] = 5;
                    break;
                }
                continue;
            } else if (chart[j1 - 1][j2] != 1) {
                j1--;
                chart[j1][j2] = 4;
                counter++;
                if ((j1 == l.end.i) && (j2 == l.end.j)) {
                    chart[j1][j2] = 5;
                    break;
                }
                if (chart[j1][j2 + 1] != 1) {
                    j2++;
                    chart[j1][j2] = 4;
                    counter++;
                    if ((j1 == l.end.i) && (j2 == l.end.j)) {
                        chart[j1][j2] = 5;
                        break;
                    }
                    continue;
                }
                continue;
            } else if (chart[j1 + 1][j2] != 1) {
                j1++;
                chart[j1][j2] = 4;
                counter++;
                if ((j1 == l.end.i) && (j2 == l.end.j)) {
                    chart[j1][j2] = 5;
                    break;
                }
                continue;
            } else if (chart[j1][j2 - 1] != 1) {
                j2--;
                chart[j1][j2] = 4;
                counter++;
                if ((j1 == l.end.i) && (j2 == l.end.j)) {
                    chart[j1][j2] = 5;
                    break;
                }
                continue;
            }
        }
        if (j1 > l.end.i) {
            if (counter > m * n) {
                break;
            }
            if (chart[j1 - 1][j2] != 1) {
                j1--;
                chart[j1][j2] = 4;
                counter++;
                if ((j1 == l.end.i) && (j2 == l.end.j)) {
                    chart[j1][j2] = 5;
                    break;
                }
                continue;
            } else if (chart[j1][j2 - 1] != 1) {
                j2--;
                chart[j1][j2] = 4;
                counter++;
                if ((j1 == l.end.i) && (j2 == l.end.j)) {
                    chart[j1][j2] = 5;
                    break;
                }
                if (chart[j1 - 1][j2] != 1) {
                    j1--;
                    chart[j1][j2] = 4;
                    counter++;
                    if ((j1 == l.end.i) && (j2 == l.end.j)) {
                        chart[j1][j2] = 5;
                        break;
                    }
                    continue;
                }
                continue;
            } else if (chart[j1][j2 + 1] != 1) {
                j2++;
                chart[j1][j2] = 4;
                counter++;
                if ((j1 == l.end.i) && (j2 == l.end.j)) {
                    chart[j1][j2] = 5;
                    break;
                }
                continue;
            } else if (chart[j1 + 1][j2] != 1) {
                j1++;
                chart[j1][j2] = 4;
                counter++;
                if ((j1 == l.end.i) && (j2 == l.end.j)) {
                    chart[j1][j2] = 5;
                    break;
                }
                continue;
            }
        }
        if (j2 > l.end.j) {
            if (counter > m * n) {
                break;
            }
            if (chart[j1][j2 - 1] != 1) {
                j2--;
                chart[j1][j2] = 4;
                counter++;
                if ((j1 == l.end.i) && (j2 == l.end.j)) {
                    chart[j1][j2] = 5;
                    break;
                }
                continue;
            } else if (chart[j1 + 1][j2] != 1) {
                j1++;
                chart[j1][j2] = 4;
                counter++;
                if ((j1 == l.end.i) && (j2 == l.end.j)) {
                    chart[j1][j2] = 5;
                    break;
                }
                if (chart[j1][j2 - 1] != 1) {
                    j2--;
                    chart[j1][j2] = 4;
                    counter++;
                    if ((j1 == l.end.i) && (j2 == l.end.j)) {
                        chart[j1][j2] = 5;
                        break;
                    }
                    continue;
                }
                continue;
            } else if (chart[j1 - 1][j2] != 1) {
                j1--;
                chart[j1][j2] = 4;
                counter++;
                if ((j1 == l.end.i) && (j2 == l.end.j)) {
                    chart[j1][j2] = 5;
                    break;
                }
                continue;
            }else if (chart[j1][j2 + 1] != 1) {
                j2++;
                chart[j1][j2] = 4;
                counter++;
                if ((j1 == l.end.i) && (j2 == l.end.j)) {
                    chart[j1][j2] = 5;
                    break;
                }
                continue;
            }
        }
    }
}

	RenderWindow window(VideoMode(800, 400), "TravelingSalesman", Style::Default);
	string chartStr = "";

	Image map_image;
	map_image.loadFromFile("tileMap.png");
	Texture mapTexture;
	mapTexture.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(mapTexture);

	while (window.isOpen()){
		window.clear(Color(255, 255, 255, 0));
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (chart[i][j] == 5)  s_map.setTextureRect(IntRect(0, 0, 32, 32));
				if (chart[i][j] == 0)  s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if ((chart[i][j] == 4)) s_map.setTextureRect(IntRect(64, 0, 32, 32));
				if ((chart[i][j] == 1)) s_map.setTextureRect(IntRect(96, 0, 32, 32));
				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);
			}
		}
		window.display();
	}
	cout << endl << "Ïóòü ïðîéäåí çà " << counter << " õîäîâ!" << endl << endl;

	for (int i = 0; i < n; i++) {
		delete[] chart[i];
	}
}
