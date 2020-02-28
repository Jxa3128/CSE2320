/*************************************
 * Group members:
 * 		Edrik Aguilera  - 1001729678
 * 		Jorge Avila     - 1001543128
 * 		Mariane Sanchez - 1001349104
 * 
 * File: merge_k.c 
 * 
 *************************************/

// includes
#include <stdlib.h>
#include <stdio.h>
#include "merge_k.h"

// Helper function to sort list
nodePT return_min( nodePT original )
{
    // Nodes to traverse the linked list
    nodePT previousNode = original;    
    nodePT currentNode = previousNode->next;
    
    // Keep track of the minimum node and the node that came before it
    nodePT minimum = currentNode;
    nodePT beforeMin = previousNode;
    
    // Traverse the entire list while finding the minimum
    while ( currentNode != NULL )
    {
    
        // If the currentNode has a smaller value than
        // current minimum, then update the minimum and its previous
        if (minimum->data > currentNode->data)
        {
            beforeMin = previousNode;
            minimum = currentNode;
        }
        
        // Continue traversing the list
        previousNode = currentNode;       
        currentNode = currentNode->next;
    }
    
    // Before returning the minimum, update the links
    // since the minimum node will be inserted into a new list
    beforeMin->next = minimum->next;
    
    return minimum;
     
}


void sort_list(nodePT L)
{
    // index variable
    int i = 0;
	int size = compute_length(L);
	
	// Create a new list
	nodePT Head = new_list();
	nodePT CurrentNode = Head;
	nodePT MinimumNode;
	
	// If size is 1 then the list is already sorted
	if ( size == 1 )
	{
		free(Head);
		return;
	}
	
	else
	{
	    // Insert the new node until the length is the same as the original
	    while ( i < size && CurrentNode != NULL )
	    {
	        // Retrieve the node with the smallest value
	        // for the current list
	        MinimumNode = return_min(L);
	        
	        // Insert the minimum into the new list
	        insert_node( CurrentNode , MinimumNode );
	        
	        // Move to the next node
	        CurrentNode = CurrentNode->next;
	        i++;
	    }
	    
	    // Have the original dummy node point to the sorted list
	    L->next = Head->next;
	    
	    // Free the extra dummy node from the new list
	    free(Head);
	    
	}
}


// Sink down function ensures that the minimum
// is always at the top of the MinHeap
void sinkDown(int k, int p, nodePT heap[k])
{

	int left = (2 * p) + 1;
	int right = (2 * p) + 2;
	int index = p;
	
	if (left < k && (heap[left]->data) < (heap[index]->data))
	{
		index = left;
	}
	if (right < k && (heap[right]->data) < (heap[index]->data))
	{
		index = right;
	}
	if (index != p)
	{
		nodePT temp = heap[p];
		heap[p] = heap[index];
		heap[index] = temp;
		sinkDown(k, index, heap);
	}
}


/* Turns the given array (named heap) into an actual Min-Heap
   using the bottom-up method to build the heap. 
   (See buidMaxHeap pseudocode in slides)
   Each single linked list starts with a dummy node. It will be easier 
   if you remove (and free) the dummy nodes of the linked lists 
   in this method before starting the work to turn the array into a heap.    
*/
void make_heap(int k, nodePT heap[k]) 
{
	
	int p, j;

	// Get rid of the dummy nodes
	for (j = 0; j < k; j++)
	{
		nodePT temp = heap[j];
		heap[j] = heap[j]->next;
		free(temp);
	}

	// Generate the MinHeap calling sinkDown
	for (p = (k / 2); p >= 0; p--)
	{
		sinkDown(k, p, heap);
	}
	
}

/*  heap is a Min-Heap of linked lists
	remove_min will remove AND RETURN the first node of the list at index 0.
	k (size of heap) will only change when that removal leaves that list empty.
*/
nodePT remove_min(int *k, nodePT heap[(*k)])
{
	// Retrieve the length to know if we must
	// update the size of the heap
	int size =  compute_length(heap[0]);

	size++; // Plus one since we erased dummy node
	
	nodePT minimum;

	// When size is 1 the removal will leave the list empty
	if (size == 1)
	{
		// Set minimum to the first element
		minimum = heap[0];

		// Place the last list in the first position
		heap[0] = heap[(*k)-1];

		// Decrement the size of the heap
		(*k)--;

		// Fix the MinHeap
		sinkDown(*k, 0, heap);

		return minimum;
	}
	else
	{
		// Set minimum to the first element
		minimum = heap[0];
		
		// Set the head of the list to the next element
		heap[0] = heap[0]->next;

		// Fix the MinHeap
		sinkDown(*k, 0, heap);
		
		return minimum;
	}
	
}

/*
   heap is a Min-Heap array of SORTED single linked lists. 
   Merging process: 
	- use the heap to identify and remove the node, np, with the smallest data out 
      of the k lists. //remove_min!!!!!!!
	- insert np at the end of result list.

   Returns: a sorted single linked list built by merging the k lists.
   The result list must have a dummy node.
*/
nodePT merge_k(int k, nodePT heap[k])
{
	// Node pointers for new list generation
	nodePT finalList = new_list();
	nodePT LastNode = finalList;
	nodePT NodeToAdd;

	// Since dummy nodes are erased set length to be k
	int length = k;

	int i = 0;
	
	// Update the length of final list with compute_length
	for (i = 0; i < k; i++)
	{
		length += compute_length(heap[i]);
	}
	
	// reset index
	i = 0;

	// Remove the minimum from the heap and add the list
	// to the end of the new list
	while (i < length)
	{
		NodeToAdd = remove_min(&k, heap);
		insert_node(LastNode,NodeToAdd);
		LastNode = LastNode->next;
		i++;
	}
	
	return finalList; 
}
