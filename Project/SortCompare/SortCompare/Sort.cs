using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace SortCompare
{
    class Sort
    {
        public int NormalSort(int[] A)
        {
            var sw = Stopwatch.StartNew();

            for (int i = 0; i < A.Length - 1; i++)
            {
                for(int j = i + 1; j < A.Length; j++)
                {
                    if(A[i] > A[j])
                    {
                        Swap(ref A[i], ref A[j]);
                    }
                }
            }

                sw.Stop();

            int time = Convert.ToInt32(sw.ElapsedMilliseconds);
            return time;
        }

        public int InsertionSort(int[] A)
        {
            var sw = Stopwatch.StartNew();
            int length = A.Length;
            int k = 2;

            while(k < length)
            {
                Insert(A, k, A[k]);
                k += 1;
            }

            sw.Stop();

            int time = Convert.ToInt32(sw.ElapsedMilliseconds);
            return time;
        }


        public int SelectionSort(int[] A)
        {
            var sw = Stopwatch.StartNew();
            int curr = 0;
            int _MinIndex;

            while(curr < A.Length)
            {
                _MinIndex = FindMin(A, curr);
                
                Swap(ref A[curr], ref A[_MinIndex]);
                curr++;
            }

            sw.Stop();

            int time = Convert.ToInt32(sw.ElapsedMilliseconds);
            return time;
        }



        public void MergeSort(int[] array, int first, int last)
        {
            /*var sw = Stopwatch.StartNew();*/

            int m;
            if(first < last){
                m = (last + first)/2;
                MergeSort(array, first, m);
                MergeSort(array, m + 1, last);
                Merge(array,first, m, last);
            }

            /*sw.Stop();*/

//             int time = Convert.ToInt32(sw.ElapsedMilliseconds);
//             return time;
        }


        public int QuickSort(int[] A)
        {
            return 1;
        }

        //Additional function
        public int[] CreateArr()
        {
            int[] A = new int[1000];

            Random rnd = new Random();

            for (int i = 0; i < 1000; i++)
            {
                A[i] = rnd.Next(0, 10000);
            }

                return A;
        }


        public string ShowArr(int[] A)
        {
            string res = "";
            for (int i = 0; i < A.Length; i++)
            {
                res += A[i].ToString() + " ";
            }

            return res;
        }

        private void Insert(int[] A, int pos, int value)
        {
            int i = pos - 1;

            while((i >= 0) && (A[i] > value))
            {
                A[i + 1] = A[i]; 
                i -= 1;
            }

            A[i + 1] = value;
        }


        private void Merge(int[] array, int first, int middle, int last)
        {
            //The array be like: first, ele, ele,.... middle | middle +1, ele, ele, ele....., last
            int[] tmp = new int[last - first + 1];
            int k = 0;
            int i = first;
            int j = middle+1;

            while((i <= middle) && (j <= last))
            {
                if (array[i] < array[j])
                {
                    tmp[k] = array[i];
                    k++;
                    i++;
                }
                else
                {
                    tmp[k] = array[j];
                    k++;
                    j++;
                }
            }

            if(i == middle+1)
            {
                while(j <= last)
                {
                    tmp[k] = array[j];
                    k++;
                    j++;
                }
            }
            else
            {
                while (i <= middle)
                {
                    tmp[k] = array[i];
                    k++;
                    i++;
                }
            }


            for (k = 0; k <= last - first; k++)
            {
                array[first + k] = tmp[k];
            }
        }


        private void Swap(ref int a, ref int b)
        {
            int temp = a;
            a = b;
            b = temp;
        }


        private int FindMin(int[] A, int s)
        {
            int _min = A[s];
            int _minIndex = s;
            for(int i = s; i < A.Length; i++)
            {
                if(_min > A[i])
                {
                    _minIndex = i;
                    _min = A[i];
                }
            }

            return _minIndex;
        }
    }
}
