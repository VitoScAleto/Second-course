#include "../Headers/Headers.h"


int main()
{
    ifstream f("../JSON/schema.json");
    json data = json::parse(f);

    cout<<data<<endl;

    return 0;
}