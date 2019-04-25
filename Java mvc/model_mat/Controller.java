package model_mat;

import java.util.Scanner;

public class Controller extends AbstractController{
	View matrixView;
	MatrixModel matrixA;
	MatrixModel matrixB;
	MatrixModel matrixC;

	static Scanner read = new Scanner( System.in );
	
	int GetUserInput() {
		int opt;
		opt = read.nextInt();
		return opt;
	}
	
	Controller()
	{
		matrixView = new View();
	}
	
	MatrixModel SetupMatrix(String which)
	{
		int xsizehold;
		int ysizehold;
		
		matrixView.PromptMatrix(which);
		matrixView.AskForMatrixSize("X");
		xsizehold = GetUserInput();
		matrixView.AskForMatrixSize("Y");
		ysizehold = GetUserInput();
		MatrixModel obj = new MatrixModel(xsizehold, ysizehold);
		int[][] arr = new int[xsizehold][ysizehold];
		
		for (int i = 0; i < xsizehold; i++)
		{
			for(int j = 0; j < ysizehold; j++)
			{
				matrixView.PromptElement(i, j);
				arr[i][j] = GetUserInput();
			}
		}
		try
		{
			obj.setModelValues(arr);			
		}
		catch(Exception e)
		{
			matrixView.PrintException(e);
		}
		
		
		return obj;
	}
	
	void WaitForUserInput() {
		int opt = -1;
		
		while(opt != 0)
		{
			matrixView.ShowMenu();
			opt = GetUserInput();
			switch(opt)
            {
                case 1:
            	{
            		matrixA = SetupMatrix("A");
            		matrixB = SetupMatrix("B");
            	}
            	break;		
                case 2:
                {
                	try
                	{
                		if(matrixA == null || matrixB == null)
                			throw new MatrixNotInitalized();
                		
                		matrixA.actionOnModel();
                    	matrixB.actionOnModel();
                	}
                	catch(Exception e)
                	{
                		matrixView.PrintException(e);
                	}
                }
                    
                break;
                case 3:
                {
                	try
                	{
                		matrixC = (MatrixModel) matrixA.actionOnModels(matrixB);
                	}
                	catch(Exception e)
                	{
                		matrixView.PrintException(e);
                	}
                }
                	
                break;
                case 4:
                {
                	try
                	{
                		if(matrixC == null)
                			throw new MatrixNotInitalized();
                		matrixC.actionOnModel();                		
                	}
                	catch(Exception e)
                	{
                		matrixView.PrintException(e);
                	}
                }
                break;
                case 5:
                {
                	try
                	{
                		if(matrixA == null || matrixB == null)
                			throw new MatrixNotInitalized();
                		
                		matrixView.PromptMatrix("A");
                		matrixView.ShowModel(matrixA);
                		
                		matrixView.PromptMatrix("B");
                        matrixView.ShowModel(matrixB);
                	}
                	catch(Exception e)
                	{
                		matrixView.PrintException(e);
                	}
                }
                break;
                case 6:
                {
                	try
                	{
                		if(matrixC == null)
                			throw new MatrixNotInitalized();
                		matrixView.ShowModel(matrixC);                		
                	}
                	catch(Exception e)
                	{
                		matrixView.PrintException(e);
                	}
                }
                break;
                case 0:
                {
                	return;
                }
                default:
                {
                	matrixView.ShowErrorInput();
                }
            	break;
            }
        }
	}
}
