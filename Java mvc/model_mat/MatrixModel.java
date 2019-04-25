package model_mat;

public class MatrixModel extends AbstrackModel{
	
	
	MatrixModel(int i, int j)
	{
		x_size = i;
		y_size = j;
		
		arr = new int[i][];
		for(int iter = 0; iter < i; iter++)
			arr[iter] = new int[j];
	}
	
	@Override
	void setModelValues(int[][] input) throws MatricesSizeNotMatching{
		
		if(input.length != x_size && input[0].length != y_size)
		{
			throw new MatricesSizeNotMatching();
		}
			
		for (int i = 0; i < x_size; i++)
		{
			for(int j = 0; j < y_size; j++)
			{
				arr[i][j] = input[i][j];
			}
		}
	}

	@Override
	int[][] getModelValues() {
		return arr;
	}

	@Override
	void actionOnModel() {//transpose
		MatrixModel obj = new MatrixModel(y_size, x_size);
		for (int i = 0; i < x_size; i++)
		{
			for(int j = 0; j < y_size; j++)
			{
				obj.arr[j][i] = this.arr[i][j];
			}
		}
		this.x_size = obj.x_size;
		this.y_size = obj.y_size;
		this.arr = obj.arr;
	}
	
	@Override
	AbstrackModel actionOnModels(AbstrackModel factor) throws MatricesSizeNotMatching{
		
		if(this.y_size != factor.x_size)
		{
			throw new MatricesSizeNotMatching();
		}
		
		AbstrackModel obj = new MatrixModel(this.x_size, factor.y_size);
		
		for(int i = 0; i < this.x_size; i++)
		{
			for(int j = 0; j < factor.y_size; j++)
			{
				obj.arr[i][j] = 0;
				for(int k = 0; k < this.y_size; k++)
				{
					obj.arr[i][j] += this.arr[i][k] * factor.arr[k][j];
				}
			}
		}
		
		return obj;
	}
}
