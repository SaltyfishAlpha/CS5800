#include <vector>
using namespace std;

// T(n) = T(n - 1) + 1 + T(n - 1) = 2 * T(n-1) + 1
//      = 2^k * T(n-k) + \sum_(i=0)^(k-1) 2^i
//      = 2^(n-1) * T(1) + \sum_(i=0)^(n-2) 2^i
//      = 2^(n-1) + 2^(n-1) - 1
//      = 2^n - 1
// T(4) = 2 * T(3) + 1 = 15
class HanoiTower
{
public:
    HanoiTower(int _n) : n(_n)
    {
        for (int i = _n; i >= 1; i--)
            towers[0].push_back(i);
    }

    void move(int number, int st, int ed)
    {
        if (*(towers[st].end()-1) != number)
        {
            cerr<<"Illegal move"<<endl;
            return;
        }
        towers[ed].push_back(number);
        towers[st].erase(towers[st].end()-1);
    }

    string render() {
        int height = n;
        int towerWidth = 2 * n + 1;

        ostringstream out;

        for (int row = height-1; row >= 0; row--) {
            for (int t = 0; t < 3; t++) {
                if (row < towers[t].size()) {
                    int disk = towers[t][row];
                    int diskWidth = 2 * disk - 1;
                    int padding = (towerWidth - diskWidth) / 2;

                    out << string(padding, ' ')
                        << string(diskWidth, '*')
                        << string(padding, ' ');
                } else {
                    int padding = (towerWidth - 1) / 2;
                    out << string(padding, ' ')
                        << "|"
                        << string(padding, ' ');
                }
                out << ' ';
            }
            out << '\n';
        }

        for (int i = 0; i < 3; i++)
            out << string(towerWidth, '=') << ' ';
        out << '\n';

        out << string(n, ' ') << "A"
            << string(towerWidth, ' ')
            << "B"
            << string(towerWidth, ' ')
            << "C\n";

        return out.str();
    }
private:
    vector<int> towers[3];
    int n;
};

class Solution {
public:

    void inline log(int number, int st, int ed)
    {
        static int i = 0;
        i++;
        cout<<"Step #"<<i<<": move Disk #"<<number<<" from Tower #"<<st<<" to Tower #"<<ed<<"\n";
    }

    void move(HanoiTower& hanoi, int n, int st, int ed)
    {
        if (n == 1)
        {
            hanoi.move(n, st, ed);
            log(n, st, ed);
            cout <<hanoi.render();
            return;
        }

        int third = (st+1)%3 == ed? (st+2)%3 : (st+1)%3;

        move(hanoi, n-1, st, third);

        hanoi.move(n, st, ed);
        log(n, st, ed);
        cout <<hanoi.render();

        move(hanoi, n-1, third, ed);
    }

    void Hanoi(int n) {
        HanoiTower hanoi(n);
        move(hanoi, n, 0, 2);
    }
};
