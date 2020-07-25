#include <bits/stdc++.h>
#define N 4
#define TARGET 16
using namespace std;

int digit(int n);
void output_board(vector<vector<int>> &b);
void update_state(vector<vector<int>> &nums, int vertical, int horizontal, bool *move);
void check(vector<vector<int>> &nums, bool *game_clear, bool *game_over);
void add(vector<vector<int>> &nums);
int calc_v_h(int v_h, int i);

int main()
{
    cout << "----------------------------------" << endl;
    cout << "| ------------------------------ |" << endl;
    cout << "| | WELCOME to 2048!           | |" << endl;
    cout << "| | Please Input               | |" << endl;
    cout << "| |         - 'i' for up       | |" << endl;
    cout << "| |         - 'j' for left     | |" << endl;
    cout << "| |         - 'k' for right    | |" << endl;
    cout << "| |         - 'm' for down     | |" << endl;
    cout << "| |         - \"exit\" for exit  | |" << endl;
    cout << "| ------------------------------ |" << endl;
    cout << "----------------------------------" << endl;
    cout << endl;

    vector<vector<int>> nums;
    for (int i = 0; i < N; i++)
    {
        nums.emplace_back(0);
        for (int j = 0; j < N; j++)
        {
            nums.at(i).emplace_back(0);
        }
    }

    nums.at(0).at(0) = 2;

    output_board(nums);

    bool game_clear = false;
    bool game_over = false;

    while (!game_clear && !game_over)
    {
        int vertical;
        int horizontal;

        cout << "-------------------------------------------------" << endl;
        cout << "Please input the command. --> ";
        while (1)
        {
            string command;
            cin >> command;
            if (command == "i" || command == "I")
            {
                vertical = -1;
                horizontal = 0;
                break;
            }
            else if (command == "j" || command == "J")
            {
                vertical = 0;
                horizontal = -1;
                break;
            }
            else if (command == "k" || command == "K")
            {
                vertical = 0;
                horizontal = 1;
                break;
            }
            else if (command == "m" || command == "M")
            {
                vertical = 1;
                horizontal = 0;
                break;
            }
            else if (command == "exit")
            {
                return 0;
            }
            else
            {
                cout << "Please input again. --> ";
            }
        }
        bool move = false;
        update_state(nums, vertical, horizontal, &move);
        check(nums, &game_clear, &game_over);

        if (move && !game_clear && !game_over)
        {
            add(nums);
        }
        output_board(nums);
    }

    if (game_clear)
    {
        cout << "Game Clear!" << endl;
    }
    else if (game_over)
    {
        cout << "Game Over!" << endl;
    }

    return 0;
}

int digit(int n)
{
    int count = 0;
    while (n != 0)
    {
        n /= 10;
        count++;
    }
    return count;
}

void output_board(vector<vector<int>> &b)
{
    for (int i = 0; i < N; i++)
    {
        cout << "---------------------" << endl;
        for (int j = 0; j < N; j++)
        {
            int output_num = b.at(i).at(j);
            cout << "|";
            if (output_num == 0)
            {
                cout << "    ";
            }
            else
            {
                for (int space = 0; space < N - digit(output_num); space++)
                {
                    cout << " ";
                }
                cout << output_num;
            }
        }

        cout << "|" << endl;
    }
    cout << "---------------------" << endl;
}

void update_state(vector<vector<int>> &nums, int vertical, int horizontal, bool *move)
{
    vector<vector<int>> new_nums;
    for (int i = 0; i < N; i++)
    {
        new_nums.emplace_back(0);
        for (int j = 0; j < N; j++)
        {
            new_nums.at(i).emplace_back(0);
        }
    }

    if (vertical == -1 && horizontal == 0)
    {
        //up
        for (int j = 0; j < N; j++)
        {
            queue<int> tmp1;
            for (int i = 0; i < N; i++)
            {
                int n = nums.at(i).at(j);
                if (n != 0)
                {
                    tmp1.push(n);
                }
            }

            queue<int> tmp3;
            while (!tmp1.empty())
            {
                int tmp2 = tmp1.front();
                tmp1.pop();

                if (!tmp1.empty() && tmp2 == tmp1.front())
                {
                    tmp2 *= 2;
                    tmp1.pop();
                }

                tmp3.push(tmp2);
            }

            int tmp3_size = tmp3.size();
            new_nums.emplace_back(0);
            for (int i = 0; i < tmp3_size; i++)
            {
                new_nums.at(i).at(j) = tmp3.front();
                tmp3.pop();
            }
        }
    }
    else if (vertical == 0 && horizontal == -1)
    {
        //left
        for (int i = 0; i < N; i++)
        {
            queue<int> tmp1;
            for (int j = 0; j < N; j++)
            {
                int n = nums.at(i).at(j);
                if (n != 0)
                {
                    tmp1.push(n);
                }
            }

            queue<int> tmp3;
            while (!tmp1.empty())
            {
                int tmp2 = tmp1.front();
                tmp1.pop();

                if (!tmp1.empty() && tmp2 == tmp1.front())
                {
                    tmp2 *= 2;
                    tmp1.pop();
                }

                tmp3.push(tmp2);
            }

            int tmp3_size = tmp3.size();
            new_nums.emplace_back(0);
            for (int j = 0; j < tmp3_size; j++)
            {
                new_nums.at(i).at(j) = tmp3.front();
                tmp3.pop();
            }
        }
    }
    else if (vertical == 0 && horizontal == 1)
    {
        //right
        for (int i = 0; i < N; i++)
        {
            queue<int> tmp1;
            for (int j = 0; j < N; j++)
            {
                int n = nums.at(i).at(N - j - 1);
                if (n != 0)
                {
                    tmp1.push(n);
                }
            }

            queue<int> tmp3;
            while (!tmp1.empty())
            {
                int tmp2 = tmp1.front();
                tmp1.pop();

                if (!tmp1.empty() && tmp2 == tmp1.front())
                {
                    tmp2 *= 2;
                    tmp1.pop();
                }

                tmp3.push(tmp2);
            }

            int tmp3_size = tmp3.size();
            new_nums.emplace_back(0);
            for (int j = 0; j < tmp3_size; j++)
            {
                new_nums.at(i).at(N - j - 1) = tmp3.front();
                tmp3.pop();
            }
        }
    }
    else if (vertical == 1 && horizontal == 0)
    { //down
        for (int j = 0; j < N; j++)
        {
            queue<int> tmp1;
            for (int i = 0; i < N; i++)
            {
                int n = nums.at(N - i - 1).at(j);
                if (n != 0)
                {
                    tmp1.push(n);
                }
            }

            queue<int> tmp3;
            while (!tmp1.empty())
            {
                int tmp2 = tmp1.front();
                tmp1.pop();

                if (!tmp1.empty() && tmp2 == tmp1.front())
                {
                    tmp2 *= 2;
                    tmp1.pop();
                }

                tmp3.push(tmp2);
            }

            int tmp3_size = tmp3.size();
            new_nums.emplace_back(0);
            for (int i = 0; i < tmp3_size; i++)
            {
                new_nums.at(N - i - 1).at(j) = tmp3.front();
                tmp3.pop();
            }
        }
    }

    //compare nums and new_nums
    *move = false;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (nums.at(i).at(j) != new_nums.at(i).at(j))
            {
                *move = true;
            }
        }
    }

    nums.clear();
    for (int i = 0; i < N; i++)
    {
        nums.emplace_back(new_nums.at(i));
    }
}

void check(vector<vector<int>> &nums, bool *game_clear, bool *game_over)
{
    vector<pair<int, int>> empty_space;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (nums.at(i).at(j) == 0)
            {
                empty_space.emplace_back(make_pair(i, j));
            }
            if (nums.at(i).at(j) == TARGET)
            {
                *game_clear = true;
                return;
            }
        }
    }

    if (empty_space.size() == 0)
    {
        *game_over = true;
        return;
    }
}

void add(vector<vector<int>> &nums)
{
    random_device rnd;
    int new_num = (rnd() % 2 + 1) * 2; //2 or 4
    vector<pair<int, int>> empty_space;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (nums.at(i).at(j) == 0)
            {
                empty_space.emplace_back(make_pair(i, j));
            }
        }
    }

    int new_num_place = rnd() % empty_space.size();
    nums.at(empty_space.at(new_num_place).first).at(empty_space.at(new_num_place).second) = new_num;
}

int calc_v_h(int v_h, int i)
{
    if (v_h == 1)
    {
        return N - i - 1;
    }
    else
    {
        return i;
    }
    return 0;
}
