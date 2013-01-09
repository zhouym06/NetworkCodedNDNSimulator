import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;


public class Main {
	//for first round
	static int[] ContentNums = {10, 100, 1000};
	static int ContentSize = 10;
	static int[] ks = {1,2,3,5,10,20,50,100};
	static double[] cachePercents = {0.1, 0.4, 0.7, 1};
	
	//for firgure1
	
	
	
	static String[] varName = {"ContentNum",  "K", "TotalCache"};
	
	static String[] dataName = {"total_cache_miss_Ratio","total_cache_miss_Count",
			"total_cache_hit_Ratio","total_cache_hit_Count",
			"total_request",
			"total_networkload",
			"total_server_load"}; 
	
	public static void main(String[] args) {
		String dir1 = "D:/NDNlog2/NDNlog-tree-l5-d2/";
		String dir2 = "D:/NDNlog2/NDNlog-linear-c_size10/";
		String dir3 = "D:/NDNlog2/NDNlog-figure1-cahce-withoutK/";
		String dir4 = "D:/NDNlog2/NDNlog-AllCache-WithUniform/";
		
		
		/*
		String prefix = "TreeTopoTest-NC";
		handle(dir1, prefix);
		prefix = "TreeTopoTest-UC";
		handle(dir1, prefix);
		prefix = "LinearTopoTest-UC";
		handle(dir2, prefix);
		prefix = "LinearTopoTest-NC";
		handle(dir2, prefix);
		
		removeUnfinished(dir3);
		handleFig1NCUC(dir3, "LinearTopoTest");
		handleFig1NCUC(dir3, "TreeTopoTest");
		*/
		handleFigK(dir4, "LinearTopoTest");
		handleFigK(dir4, "TreeTopoTest");
		handleFigK(dir4, "TestUniformLinear");
		handleFigK(dir4, "TestUniformTree");
		
		
		
	}

	private static void handleFigK(String dir, String prefix) {
		double[][][][] dataNC = new double[4][10][5][7];
		double[][][][] dataUC = new double[4][10][5][7];
		for(int ContentNum_i = 0; ContentNum_i < 3; ContentNum_i++)
		{
			for(int cp_i = 1; cp_i <= 10; cp_i += 1)
			{
				for(int k_i = 0; k_i < 5; k_i++)
				{
					int k = ks[k_i];
					dataNC[ContentNum_i][cp_i - 1][k_i] = GetData(dir, prefix + "-NC", ContentNums[ContentNum_i], k, (int)(ContentNums[ContentNum_i] * ContentSize * cp_i / 10));
					dataUC[ContentNum_i][cp_i - 1][k_i] = GetData(dir, prefix + "-UC", ContentNums[ContentNum_i], k, (int)(ContentNums[ContentNum_i] * ContentSize * cp_i / 10));					
				}
			}
			koutput(dir + prefix + "-ContentNum" + ContentNums[ContentNum_i], ContentNum_i, dataNC[ContentNum_i], dataUC[ContentNum_i]);
		}
	}

	private static void koutput(String folder, int contentNum_i, double[][][] dataNC,
			double[][][] dataUC) {
		File f = new File(folder);
		f.mkdirs();
		
		String fileName = folder + "/" + "result" + ".txt"; 
		
		f = new File(fileName);
		try {
			if(!f.exists())
				f.createNewFile();
			
			BufferedWriter out = new BufferedWriter(new FileWriter(f));
			for(int dataIndex = 0; dataIndex < 7; dataIndex++)
			{
				
				out.write(dataName[dataIndex] + ":\r\n");
				out.write("\r\n\t");
				for(int k_i = 0; k_i < 5; k_i++)
				{
					out.write("\t" + ks[k_i]);
				}
				out.write("\r\n");
				out.write("NC  :");
				for(int i = 1; i <= 10; i++)
				{
					out.write("\t" + ContentNums[contentNum_i] * ContentSize * i / 10);
					for(int k_i = 0; k_i < 5; k_i++)
					{
						out.write("\t" + dataNC[i-1][k_i][dataIndex]);
					}
					out.write("\r\n");
				}
				out.write("\r\n\t");
				for(int k_i = 0; k_i < 5; k_i++)
				{
					out.write("\t" + ks[k_i]);
				}
				out.write("\r\n");
				out.write("UC  :");
				for(int i = 1; i <= 10; i++)
				{
					out.write("\t" + ContentNums[contentNum_i] * ContentSize * i / 10);
					for(int k_i = 0; k_i < 5; k_i++)
					{
						out.write("\t" + dataUC[i-1][k_i][dataIndex]);
					}
					out.write("\r\n");
				}

				out.write("\r\n");
				out.write("\r\n");
			}
			
			
			/*
			for(int dataIndex = 0; dataIndex < 7; dataIndex++)
			{
				
				out.write(dataName[dataIndex] + ":\r\n");
				out.write("\r\n");
				for(int i = 1; i <= 10; i++)
				{
					out.write("\t" + ContentNums[contentNum_i] * ContentSize * i / 10);
				}
				out.write("\r\n");
				out.write("NC  :\t");
				for(int i = 1; i <= 10; i++)
				{
					out.write(dataNC[i-1][dataIndex] + "\t");
				}
				out.write("\r\n");
				out.write("UC  :\t");
				for(int i = 1; i <= 10; i++)
				{
					out.write(dataUC[i-1][dataIndex] + "\t");
				}
				out.write("\r\n");
				out.write("\r\n");
			}
			*/
			out.close();
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		//
	}

	private static void handleFig1NCUC(String dir, String prefix) {
		double[][][] dataNC = new double[4][10][7];
		double[][][] dataUC = new double[4][10][7];
		for(int ContentNum_i = 0; ContentNum_i < 3; ContentNum_i++)
		{
			int k = 10000;
			for(int cp_i = 1; cp_i <= 10; cp_i += 1)
			{		
				dataNC[ContentNum_i][cp_i - 1] = GetData(dir, prefix + "-NC", ContentNums[ContentNum_i], k, (int)(ContentNums[ContentNum_i] * ContentSize * cp_i / 10));
				dataUC[ContentNum_i][cp_i - 1] = GetData(dir, prefix + "-UC", ContentNums[ContentNum_i], k, (int)(ContentNums[ContentNum_i] * ContentSize * cp_i / 10));					
			}
			fig1output(dir + prefix + "-ContentNum" + ContentNums[ContentNum_i], ContentNum_i, dataNC[ContentNum_i], dataUC[ContentNum_i]);
		}
		
	}

	private static void fig1output(String folder, int contentNum_i,
			double[][] dataNC, double[][] dataUC) {
		File f = new File(folder);
		f.mkdirs();
		
		String fileName = folder + "/" + "result" + ".txt"; 
		f = new File(fileName);
		try {
			if(!f.exists())
				f.createNewFile();
			
			BufferedWriter out = new BufferedWriter(new FileWriter(f));
			
			for(int dataIndex = 0; dataIndex < 7; dataIndex++)
			{
				
				out.write(dataName[dataIndex] + ":\r\n");
				out.write("\r\n");
				for(int i = 1; i <= 10; i++)
				{
					out.write("\t" + ContentNums[contentNum_i] * ContentSize * i / 10);
				}
				out.write("\r\n");
				out.write("NC  :\t");
				for(int i = 1; i <= 10; i++)
				{
					out.write(dataNC[i-1][dataIndex] + "\t");
				}
				out.write("\r\n");
				out.write("UC  :\t");
				for(int i = 1; i <= 10; i++)
				{
					out.write(dataUC[i-1][dataIndex] + "\t");
				}
				out.write("\r\n");
				out.write("\r\n");
			}
			out.close();
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	private static void handle(String dir, String prefix) {
		double[][][][] datas = new double[4][4][8][7];
		for(int ContentNum_i = 0; ContentNum_i < 3; ContentNum_i++)
		{
			for(int cp_i = 0; cp_i < 4; cp_i++)
			{
				for(int k_i = 0; k_i < 8; k_i++)
				{
					datas[ContentNum_i][cp_i][k_i] = GetData(dir, prefix, ContentNums[ContentNum_i], ks[k_i], (int)(ContentNums[ContentNum_i] * ContentSize * cachePercents[cp_i]));
				}
			}
			output(dir + prefix + "-ContentNum" + ContentNums[ContentNum_i], ContentNum_i, datas[ContentNum_i]);
		}
	}

	private static double[] GetData(String dir, String prefix, int ContentNum, int k, int cacheSize) {
		double[] data = new double[7];
		String fileName = dir + prefix + "-ContentNum" + ContentNum + "-ContentSize10-K" + k + "-TotalCache" + cacheSize + ".txt";
		File f = new File(fileName);
		if(!f.exists())
		{
			System.out.println("File doesn't exist:" + fileName);
			return data;
		}
		try {
			BufferedReader input = new BufferedReader(new FileReader(f));
			for(String line = input.readLine(); line != null;line = input.readLine())
			{
				if(line.startsWith("total_cache_miss"))
				{
					String[] s = line.split("\t");
					data[0] = Double.valueOf(s[1]);
					data[1] = Double.valueOf(s[2]);
				}
				if(line.startsWith("total_cache_hit"))
				{

					String[] s = line.split("\t");
					data[2] = Double.valueOf(s[1]);
					data[3] = Double.valueOf(s[2]);
				}
				if(line.startsWith("total_request"))
				{
					String[] s = line.split("\t");
					data[4] = Double.valueOf(s[1]);
				}
				if(line.startsWith("total_networkload"))
				{
					String[] s = line.split("\t");
					data[5] = Double.valueOf(s[1]);
					
				}
				if(line.startsWith("total_server_load"))
				{
					String[] s = line.split("\t");
					data[6] = Double.valueOf(s[1]);
				}
			}
			input.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return data;
	}

	private static void output(String folder, int contentNum_i, double[][][] datas) {
		File f = new File(folder);
		f.mkdirs();
		for(int dataIndex = 0; dataIndex < 7; dataIndex++)
		{
			String fileName = folder + "/" + dataName[dataIndex] + ".txt"; 
			f = new File(fileName);
			
			try {
				if(!f.exists())
					f.createNewFile();
				
				BufferedWriter out = new BufferedWriter(new FileWriter(f));
				out.write("x: cacheSize :");
				for(int i = 0; i < 4; i++)
				{
					out.write("\t" + ContentNums[contentNum_i] * 10 * cachePercents[i]);
				}
				out.write("\r\ny: k :");
				for(int i = 0; i < 8; i++)
				{
					out.write("\t" + ks[i]);
				}
				out.write("\r\n");
				for(int i = 0; i < 4; i++)
				{
					for(int j = 0; j < 8; j++)
					{
						out.write(datas[i][j][dataIndex] + "\t");
					}
					out.write("\r\n");
				}
				out.close();
				
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			
		}
		
		
	}
	public static void removeUnfinished(String folder)
	{
		File dir = new File(folder);
		File file[] = dir.listFiles();
		for (int i = 0; i < file.length; i++) 
		{
			if(!file[i].isDirectory())
			{
				if(!finished(file[i]))
				{
					System.out.println("removeUnfinished " + file[i].getName());
					File f=  file[i];
					f.delete();
				}				
			}
		}
	}
	public static boolean finished(File f)
	{
		String lastLine="";
		try {
			BufferedReader input = new BufferedReader(new FileReader(f));
			String nextLine="";
			do
			{
				lastLine = nextLine;
				nextLine = input.readLine();
			}while( nextLine!= null);
			input.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		//System.out.println(f.getName() + "\t" + lastLine);
		
		if(lastLine.startsWith("Statistic::Display() fin."))
			return true;
		return false;
	}

}
