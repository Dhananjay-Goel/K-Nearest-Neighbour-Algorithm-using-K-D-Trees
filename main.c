#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include<limits.h>

// DIMENSION IS K
// X IS NO OF NEAREST WE WANT TO FIND

struct Node_Queue 
// Making a structure which creates priority queue
{
    int *arr;// Stores the points
    int priority;// Stores the distance of point from target point
};
typedef struct Node_Queue node_queue ;

node_queue * queue = NULL;
int size = -1;
// Declaring a global queue and size of that queue

void enqueue(int array[], int dist, int k)
// Function to insert element in the priority queue
{
    size++;
    if (size>0)
    {
        queue = (node_queue*)realloc(queue,(size+1)*sizeof(node_queue));
    }
    queue[size].arr = (int*)malloc(k*sizeof(int)); 
    // Allocating size to queue and each arr in queue
    for (int i = 0; i < k; i++)
    {
        queue[size].arr[i]=array[i];
    }
    queue[size].priority = dist;
    // Inserting the array and distance as priority to the queue
}


int max_index(int x,int k)
//finding the index of the max element in the queue
{
    int largest = 0;
    for (int i = 1; i < x; i++)
    {
        if (queue[largest].priority<=queue[i].priority)
        {
            largest=i;
        }
    }
    return largest;
    // Returning the Index of largest Element priority in priority queue
}

struct Node
//structure of node of K-D Tree
{
    int *point;
    struct Node *left, *right;
};
typedef struct Node node;

node* new_node(int arr[],int k)
// Creating new node in tree
{
    node* newnode= (node*)malloc(sizeof(node));
    newnode->point= (int*)malloc(k*sizeof(int));

    for (int i = 0; i < k; i++)
    {
        *(newnode->point+i)=arr[i];
    }
    newnode->left=NULL;
    newnode->right=NULL;
    return newnode;
}   

node* insert(node* root, int arr[], int depth_node, int k)
// Inserting a point in tree
{
    if (root==NULL)
    {
        return new_node(arr,k);
    }
    int dimension= depth_node%k;
    if (*(root->point+dimension)<=arr[dimension])
    {
        root->right=insert(root->right,arr,depth_node+1,k);
    }
    else
    {
        root->left=insert(root->left,arr,depth_node+1,k);
    }
    return root;
}

int search_node(node* root, int arr[], int depth_node, int k)
//searching for a point in the tree
{
    if (root == NULL)
    {
        return 0;
    }
    int flag=1;
    for (int i = 0; i < k; ++i)
    {
        if (root->point[i] != arr[i])
        {
            flag=0;
            break;
        }
    }
    if (flag==1)
    {
        return 1;
    }
    int dimension = depth_node % k;
    if (*(root->point+dimension)<=arr[dimension])
    {
        return search_node(root->right, arr, depth_node + 1, k);
    }
    else
    {
        return search_node(root->left, arr, depth_node + 1, k);
    }   
}

node *findMin(node* root, int d, int depth, int k)
// Function to finding minimum point 
{
    if (root == NULL)
    {
        return NULL;
    }
    int dimension = depth % k;
    
    if (dimension == d)
    {
        if (root->left == NULL)
        {
            return root;   
        }
        return findMin(root->left, d, depth+1, k);
    }
    node* minNode= root;
    if( findMin(root->left,d,depth+1, k)!=NULL && findMin(root->left,d,depth+1, k)->point[d]<minNode->point[d])
    {
        minNode= findMin(root->left,d,depth+1, k);
    }
    if (findMin(root->right,d,depth+1, k)!=NULL && findMin(root->right,d,depth+1, k)->point[d]<minNode->point[d])
    {
        minNode= findMin(root->right,d,depth+1, k);
    }
    return minNode;
}

node *deleteNode(node* root_node, int arr_point[], int depth_node, int k)
// Function to delete a node
{
    if (root_node == NULL)
        return NULL;
        
    int dimension = depth_node % k;
  
    int flag=1;
    for (int i = 0; i < k; ++i)
    {
        if (root_node->point[i] != arr_point[i])
        {
            flag=0;
            break;
        }
    }
    if (flag==1)
    {
        if (root_node->right != NULL)
        {
            node *min = findMin(root_node->right, dimension,0, k);
 
            for (int i=0; i<k; i++)
                root_node->point[i] = min->point[i];

            root_node->right = deleteNode(root_node->right, min->point, depth_node+1, k);
        }
        else if (root_node->left != NULL)
        {
            node *min = findMin(root_node->left, dimension,0, k);
            for (int i=0; i<k; i++)
                root_node->point[i] = min->point[i];

            root_node->right = deleteNode(root_node->left, min->point, depth_node+1, k);
        }
        else 
        {
            free (root_node);
            return NULL;
        }
        return root_node;
    }

    if (arr_point[dimension] >= root_node->point[dimension])
    {
        root_node->right = deleteNode(root_node->right, arr_point, depth_node+1, k);
    }
    else
    {
        root_node->left = deleteNode(root_node->left, arr_point, depth_node+1, k);
    }
    return root_node;
}

int distancesqaured(int point1[], int *point2, int k)
// Calculating Eucledian distance between Two Points
{
    int distance=0;
    for (int i = 0; i < k; i++)
    {
        distance=distance+pow(point1[i]-point2[i],2);
    }
    return distance;
}

node* closest(node* node2, node* node3, int point1[],  int k)
// Function to get the closet of the two nodes from the Point
{
    if (node2 == NULL) 
    {
        return node3;
    }

    if (node3 == NULL) 
    {
        return node2;
    }

    int d1 = distancesqaured(point1, node2->point, k);
    // Distance 
    int d2 = distancesqaured(point1, node3->point, k);
    // Distance 

    if (d1 < d2)
    {
        return node2;
    }
    else
    {
        return node3;
    }
}

//function to the get the nearest Neighbour
node * nearestNeighbour(node* root, int point1[], int depth, int k)
{
    node* nextBranch;
    node* otherBranch;
    if (root==NULL)
    {
        return NULL;
    }
    if (point1[depth % k] < root->point[depth % k])
    {
        nextBranch = root->left;
        otherBranch = root->right;
    }
    else
    {
        nextBranch = root->right;
        otherBranch = root->left;
    }

    node* temp = nearestNeighbour(nextBranch,point1,depth+1,k);
    node* best = closest(temp, root, point1, k);

    int radiussquared = distancesqaured(point1, best->point, k);
    int dist = point1[depth%k] - root->point[depth%k];

    if (radiussquared >= dist*dist)
    {
        temp = nearestNeighbour(otherBranch, point1, depth+1, k);
        best = closest(temp, best, point1, k);
    }

    return best;
}

//KNN Algorithm
void knearestNeighbour(node* root, int point1[], int depth, int k, int x)
{
    node* nextBranch;
    node* otherBranch;
    if (root==NULL)
    {
        return;
    }

    if (point1[depth % k] < root->point[depth % k])
    {
        nextBranch = root->left;
        otherBranch = root->right;
    }
    else
    {
        nextBranch = root->right;
        otherBranch = root->left;
    }

    knearestNeighbour(nextBranch,point1,depth+1,k,x);
    int distanc = distancesqaured(point1, root->point, k);
    int index;
    int maxdist;
    if (size<x-1)
    {
        enqueue(root->point,distanc,k);
    }
    else
    {
        index = max_index(x,k);
        maxdist = queue[index].priority;
        if (distanc<maxdist)
        {            
            for (int i = 0; i < k; i++)
            {        
                queue[index].arr[i]=root->point[i];
                queue[index].priority=distanc;
            }
        }
    }
    
    if (size<x-1)
    {
        knearestNeighbour(otherBranch, point1, depth+1, k,x);
    }
    else
    {
        index = max_index(x,k);
        maxdist = queue[index].priority;
        int dist = point1[(depth)%k] - root->point[(depth)%k];
        if ((maxdist >= dist*dist))
        {
            knearestNeighbour(otherBranch, point1, depth+1, k,x);
        }
    }
}

void swapping(int index, int x, int k)
{
    int temp[k];
    int temppriority;
    for (int i = 0; i < k; i++)
    {
        temp[i] = queue[index].arr[i];
    }
    temppriority = queue[index].priority;
    for (int i = 0; i < k; i++)
    {
        queue[index].arr[i] = queue[x-1].arr[i];
    }
    queue[index].priority=queue[x-1].priority;
    for (int i = 0; i < k; i++)
    {
        queue[x-1].arr[i] = temp[i];
    }
    queue[x-1].priority = temppriority;
}

void sort_queue(int nearest, int k)
{
    if (nearest==0)
    {
        return;
    }
    int index;
    index = max_index(nearest,k);
    swapping(index,nearest,k);
    nearest--;
    sort_queue(nearest,k);
}

int main()
{
    //getting inputs from input text file
    FILE * filePointer; 
    filePointer = fopen("input.txt", "r");

    //dimension of the point
    int k;
    fscanf(filePointer,"%d",&k);

    //number of nearest neighbours to find
    int x;
    fscanf(filePointer,"%d",&x);

    //number of points in the data sample
    int number_points;
    fscanf(filePointer,"%d",&number_points);
    
    node *root = NULL;
    
    //point1 around which we find x nearest neighbours
    int point1[k];
    for (int i = 0; i < k; i++)
    {
        fscanf(filePointer,"%d",&point1[i]);
    }

    //array having the points
    int *points[number_points];
    for (int i = 0; i < number_points; i++)
    {
        points[i]=(int*)malloc(k*sizeof(int));
    }
    printf("\n\n");

    for (int i = 0; i < number_points; i++)
    {
        for (int j = 0; j < k; j++)
        {
            fscanf(filePointer,"%d ",&points[i][j]);
        }
    }
 
    //insertion of the points in tree
    for (int i=0; i<number_points; i++)
    {
        root = insert(root, points[i], 0, k);
    }
    
    queue=(node_queue*)malloc(sizeof(node_queue));
    node* temp;

    knearestNeighbour(root,point1,0,k,x);
    int nearest = x;
    sort_queue(nearest,k);

    printf("Results of Application OF KNN Algorithm :\n");
    for (int i = 0; i < x; i++)
    {        
        printf("%d Nearest Point is {",i+1);
        for (int j = 0; j < k-1; j++)
        {           
            printf("%d-",queue[i].arr[j]);
        }
        for (int j = k-1; j < k; j++)
        {
            printf("%d}",queue[i].arr[j]);
        }
        printf(" at a Distance: %f\n",sqrt(queue[i].priority));
    }
    printf("\n\n");

    printf("Finding Minimum Neighbour and then Deleting them and then finding Minimum Neighbour till we get given number of neighbours :\n");
    for (int i = 0; i < x; i++)
    {    
        temp = nearestNeighbour(root,point1,0,k);
        printf("%d Nearest Point is {",i+1);
        for (int i = 0; i < k-1; i++)
        {           
            printf("%d-",temp->point[i]);
        }
        for (int i = k-1; i < k; i++)
        {
            printf("%d}",temp->point[i]);
        } 
        int x = distancesqaured(temp->point,point1,k);
        printf(" at a Distance: %f\n",sqrt(x));
        root = deleteNode(root,temp->point,0,k);
    }
    return 0;
}
