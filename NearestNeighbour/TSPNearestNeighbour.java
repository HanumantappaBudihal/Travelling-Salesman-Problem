import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;
import java.util.Stack;
 
public class TSPNearestNeighbour
{
    private int numberOfNodes;
    private Stack<Integer> stack;
    private static int distance;
    private static int rtn;
 
    public TSPNearestNeighbour()
    {
        stack = new Stack<Integer>();
    }
 
    public void tsp(int adjacencyMatrix[][])
    {
        numberOfNodes = adjacencyMatrix[1].length - 1;
        int[] visited = new int[numberOfNodes + 1];
        visited[1] = 1;
        stack.push(1);
        int element, dst = 0, i;
        int min = Integer.MAX_VALUE;
        boolean minFlag = false;
        System.out.print(1 + " ");
 
        while (!stack.isEmpty())
        {
            element = stack.peek();
            i = 1;
            min = Integer.MAX_VALUE;
            while (i <= numberOfNodes)
            {
                if (adjacencyMatrix[element][i] > 1 && visited[i] == 0)
                {
                    if (min > adjacencyMatrix[element][i])
                    {
                        min = adjacencyMatrix[element][i];
                        dst = i;
                        minFlag = true;
                    }
                }
                i++;
            }
            if (minFlag)
            {
            	distance += adjacencyMatrix[element][dst];
                visited[dst] = 1;
                stack.push(dst);
                System.out.print(dst + " ");
                minFlag = false;
                continue;
            }
            rtn = dst;
            stack.pop();
        }
    }
 
    public static void main(String[] arg) throws FileNotFoundException
    {	
    	long startMili=System.currentTimeMillis();
        int number_of_nodes;
        Scanner scanner = new Scanner(new FileReader("TSP.txt"));
        number_of_nodes = scanner.nextInt();
        int adjacency_matrix[][] = new int[number_of_nodes + 1][number_of_nodes + 1];
        for (int i = 1; i <= number_of_nodes; i++)
        	{
                for (int j = 1; j <= number_of_nodes; j++)
                {
                    adjacency_matrix[i][j] = scanner.nextInt();
                }
            }
        for (int i = 1; i <= number_of_nodes; i++)
            {
                for (int j = 1; j <= number_of_nodes; j++)
                {
                    if (adjacency_matrix[i][j] == 1 && adjacency_matrix[j][i] == 0)
                    {
                        adjacency_matrix[j][i] = 1;
                    }
                }
            }
        System.out.println("the citys are visited as follows");
        TSPNearestNeighbour tspNearestNeighbour = new TSPNearestNeighbour();
        tspNearestNeighbour.tsp(adjacency_matrix);
        System.out.println();
        long endMili=System.currentTimeMillis();
        distance = distance + adjacency_matrix[1][rtn];
        System.out.println("distance: " + distance);
        System.out.println("run time: " + (endMili - startMili) + "ms");
        scanner.close();
    }
}
