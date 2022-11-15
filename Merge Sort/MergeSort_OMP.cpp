// 2 реализации на OMP: через sections и tasks. Текущая версия работает через sections, чтобы получить версию, работающую через tasks, 
// неоходимо раскоментировать код и убрать блок кода с sections. Sections в лучшем случае позволяют получить выигрыш по времени в 2 раза 
// (у меня вышло намного меньше, в лучшем случае ~1.25), поэтому, чтобы выигрыш был пропорционален количеству потоков, лучше использовать tasks
// (но я не проверяла, что таски действительно дают хороший выигрыш, это чисто теоретически).
// НО!!! tasks появляются в 3 версии OMP, т.е. в OMP 3.0, а Visual Studio поддерживает только версию 2.0. Так что жопа будет больно болеть, если 
// захотите использовать таски в вижуал студии.

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <omp.h>

using namespace std;

vector<int> sort(vector<int> a);
vector<int> merge(vector<int> a1, vector<int> a2);

int main()
{
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<> dist(0, 200);

   vector<int> vect;
   vector<int> vect2;
   for (int i = 0; i < 10; i++) {
       vect.push_back(dist(gen));
   }

   float result = 0;
   for (int i = 0; i < 5; i++) {
       auto start = std::chrono::high_resolution_clock::now();

       // через таски
       // #pragma omp parallel {
       //      #pragma omp single
       		vect2 = sort(vect)
       // }
       auto end = std::chrono::high_resolution_clock::now();
       float time_took = std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();

       result += time_took;
   }
   for (int i = 0; i < vect.size(); i++) {
       cout << vect2[i] << " ";
   }
   
   printf("Time consistent %f \n", result/5);
}

vector<int> sort(vector<int> a)
{
   if (a.size() == 1) {
       return a;
   }
   vector<int> a2(a.size() / 2);
   for (int i = 0; i < a.size() / 2; i++) {
       a2[i] = a[a.size() - a.size() / 2 + i];
   }
   a.resize(a.size() - a.size() / 2);

   vector<int> f, s;

   // через секции
   #pragma omp parallel sections shared(f, s) nowait
   {
       #pragma omp section
       {
           f = sort(a);
       }
       #pragma omp section
       {
           s = sort(a2);
       }
   }

   // через таски
   //#pragma omp task
   //f = sort(a);
   //#pragma omp task
   //s = sort(a2);

   printf("thread %d \n", omp_get_thread_num());

   // через таски
   //#pragma omp taskwait
   return merge(f, s);
}

vector<int> merge(vector<int> a1, vector<int> a2)
{
   int i = 0;
   int j = 0;
   int k = 0;
   vector<int> c(a1.size() + a2.size());
   while (i < a1.size() && j < a2.size()) {
       if (a1[i] <= a2[j]) {
           c[k++] = a1[i++];
       }
       else {
           c[k++] = a2[j++];
       }
   }
   while (j < a2.size()) {
       c[k++] = a2[j++];
   }
   while (i < a1.size()) {
       c[k++] = a1[i++];
   }
   return c;
}