// brief description: n cities in a circle. Each has a road with its neighbour.
// There exists k capitals.
// As is known to all, the capital has a road with any other cities
// and there only exists ONE road between two cities;
// Sum up the ci * cj of each road.(ci, cj are the value of cities bonded by the specific road)

// main idea:   Calculate the sum of roads in the edge of the circle. Then add the roads between the capital and others(except its neighbour)
//              Finally, substract the extra roads calculated one more time between capitals

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n = 0, k = 0;         // n cities, k capitals as the question requests
    long int sum = 0;         // the sum of ci * cj of roads
    long int city_sum = 0;    // the sum of ci of cities
    long int capital_sum = 0; // the sum of value of capitals
    scanf("%d%d", &n, &k);

    long int *c = (long int *)malloc(sizeof(long int) * n); // c:store the value of city

    // sum up the ci * cj of the roads in the edge of the circle
    scanf("%ld", &c[0]);
    city_sum += c[0];
    // the first city should be dealed with first so that sum can be operated in the for interation

    for (int i = 1; i < n; i++)
    {
        scanf("%ld", &c[i]);
        city_sum += c[i];       // sum up the ci of cities
        sum += c[i - 1] * c[i]; // sum up the ci*cj of the roads in the edge
    }
    sum += c[n - 1] * c[0]; // Don't forget the road between the last road and the first road!

    int *id = (int *)malloc(sizeof(int) * k); // id: the capital id in c[i]

    // sum up ci of capital * cj of others (except the neighbour and itself)
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &id[i]);
        id[i]--; // to match with subscripts of c array
        capital_sum += c[id[i]];
        sum += (city_sum - c[(id[i] + 1) % n] - c[(id[i] == 0) ? n - 1 : id[i] - 1] - c[id[i]]) * c[id[i]];
        //  (city_sum - left city - right city - capital itself) equals to the sum of ci of others (except its two neighbours and itself)
    }

    // after the two operations above, the roads between capitals which are not neighbours with each other have been added twice
    // the following substract the redundant road between capitals
    for (int i = 0; i < k; i++)
    {
        int j = (i + 1) % k;
        if (id[j] - id[i] == 1 || id[i] - id[j] == n - 1) // the two capitals are neighbours with each other
        {
            sum -= (capital_sum - c[id[i]] - c[id[j]]) * c[id[i]];
            // substract the roads calculated one more time among id[i] city and others(except the neighbour id[j])
        }
        else // not neighbours
        {
            sum -= (capital_sum - c[id[i]]) * c[id[i]];
        }

        capital_sum -= c[id[i]];
        // the road among the id[i] city and other cities shouldn't be substracted again in the next interation, so remove it from the capital_sum
    }

    printf("%ld", sum);
    return 0;
}