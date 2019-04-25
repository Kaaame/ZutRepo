package model_mat;

public abstract class AbstrackModel {
	protected int[][] arr;
	protected int x_size;
	protected int y_size;
	
	abstract void setModelValues(int[][] i) throws Exception;
	abstract int[][] getModelValues();
	abstract void actionOnModel();
	abstract AbstrackModel actionOnModels(AbstrackModel factor) throws Exception;
}