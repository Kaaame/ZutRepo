package model_mat;

public abstract class AbstractView {
	//static Scanner read = new Scanner( System.in );
	
	
	abstract void ShowMenu();
	abstract void ShowModel(AbstrackModel obj);
	abstract void ShowErrorInput();
	abstract void PrintException(Exception e);
}