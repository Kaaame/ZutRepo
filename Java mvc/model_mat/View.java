package model_mat;

public class View extends AbstractView{
	@Override
	void ShowMenu() {
		System.out.print("Wybierz opcje:\n");
        System.out.print("[1] Wprowadz macierze wejsciowe A i B\n");
        System.out.print("[2] Transponuj macierze A i B\n");
        System.out.print("[3] Pomnoz macierze A i B\n");
        System.out.print("[4] Transponuj macierz C\n");
        System.out.print("[5] Wyswietla macierze A i B\n");
        System.out.print("[6] Wyswietla macierz C\n");
        System.out.print("[0] Wyjscie\n");
        System.out.print("-----------------------------------\n");
        System.out.print(">>>");
	}

	void ShowModel(MatrixModel obj) {
		// TODO Auto-generated method stub
		int[][] arr = obj.getModelValues();
		for(int i = 0; i < arr.length; i++)
		{
			for(int j = 0; j < arr[0].length; j++)
			{
				System.out.print(arr[i][j] + "\t");
			}
			System.out.print("\n");
		}
	}
	void AskForMatrixSize(String which)
	{
		System.out.print("Podaj wymiar " + which + "\n");
	}
	
	void PromptMatrix(String which)
	{
		System.out.print("Znajdujesz sie na macierzy " + which + "\n");
	}
	
	void PromptElement(int i, int j)
	{
		System.out.print("Wartosc miejsca: [" + i + "][" + j + "]\n");
	}
	
	@Override
	void ShowErrorInput() {
		System.out.print("Zla opcja\n");
	}

	@Override
	void ShowModel(AbstrackModel obj) {
		ShowModel((MatrixModel)obj);
	}

	@Override
	void PrintException(Exception e) {
		// TODO Auto-generated method stub
		 System.err.println("Zlapano wyjatek: " + e.toString() + "\n");
	}
	
	

}
