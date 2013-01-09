import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.LineNumberReader;

public class Main {

	public static void main(String[] args) {
		/*
		 * removeUnfinished();
		 * 
		 * File dir = new File("D:/NDNlog/"); File file[] = dir.listFiles(); for
		 * (int i = 0; i < file.length; i++) { if(!finished(file[i])) {
		 * System.out.println("removeUnfinished" + file[i].getAbsolutePath()); }
		 * }
		 */

		for (int i = 0; true; i++) {
			removeUnfinished();
			openMyExe();
			;
			/*
			 * System.out.println(i); Runtime rn = Runtime.getRuntime(); Process
			 * p1 = null; try { p1 =
			 * rn.exec("D:/lab/NCedNDNSimulator/Release/NCedNDNSimulator.exe");
			 * p1.waitFor(); } catch (Exception e) { e.printStackTrace(); }
			 */
		}

	}

	public static void openMyExe() {
		/*
		 * Runtime rn = Runtime.getRuntime(); Process p = null; try { p =
		 * rn.exec("\"D:/lab/NCedNDNSimulator/Release/NCedNDNSimulator.exe"); }
		 * catch (Exception e) { e.printStackTrace(); }
		 */

		try {
			Runtime rt = Runtime.getRuntime();
			Process p = rt
					.exec("\"D:/lab/NCedNDNSimulator/Release/NCedNDNSimulator.exe");
			// 获取进程的标准输入流
			final InputStream is1 = p.getInputStream();
			// 获取进城的错误流
			final InputStream is2 = p.getErrorStream();
			// 启动两个线程，一个线程负责读标准输出流，另一个负责读标准错误流
			Thread t2 = new Thread() {
				public void run() {
					BufferedReader br1 = new BufferedReader(
							new InputStreamReader(is1));
					try {
						String line1 = null;
						while ((line1 = br1.readLine()) != null) {
							if (line1 != null) {
							}
						}
					} catch (IOException e) {
						e.printStackTrace();
					} finally {
						try {
							is1.close();
						} catch (IOException e) {
							e.printStackTrace();
						}
					}
				}
			};
			t2.start();

			Thread t1 = new Thread() {
				public void run() {
					BufferedReader br2 = new BufferedReader(
							new InputStreamReader(is2));
					try {
						String line2 = null;
						while ((line2 = br2.readLine()) != null) {
							if (line2 != null) {
							}
						}
					} catch (IOException e) {
						e.printStackTrace();
					} finally {
						try {
							is2.close();
						} catch (IOException e) {
							e.printStackTrace();
						}
					}
				}
			};
			t1.start();

			p.waitFor();
			p.getErrorStream().close();
			p.getInputStream().close();
			p.getOutputStream().close();

			
			t1.stop();;
			t2.stop();;
			p.destroy();
			System.out.println("proc exited,restarting");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void removeUnfinished() {
		File dir = new File("D:/NDNlog/");
		File file[] = dir.listFiles();
		for (int i = 0; i < file.length; i++) {
			if (!finished(file[i])) {
				System.out.println("removeUnfinished " + file[i].getName());
				File f = file[i];
				f.delete();
			}
		}

	}

	public static boolean finished(File f) {
		String lastLine = "";
		try {
			BufferedReader input = new BufferedReader(new FileReader(f));
			String nextLine = "";
			do {
				lastLine = nextLine;
				nextLine = input.readLine();
			} while (nextLine != null);
			input.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		// System.out.println(f.getName() + "\t" + lastLine);

		if (lastLine.startsWith("Statistic::Display() fin."))
			return true;
		return false;
	}

	public static void deleteLast() {
		File dir = new File("D:/NDNlog/");
		File file[] = dir.listFiles();
		long latest = 0;
		java.util.Date latestDate = new java.util.Date(0);
		File last_modified_file = dir;
		for (int i = 0; i < file.length; i++) {
			long modifiedTime = file[i].lastModified();
			if (latestDate.before(new java.util.Date(modifiedTime))) {
				latestDate = new java.util.Date(modifiedTime);
				last_modified_file = file[i];
			}

		}
		System.out.println();
		System.out.println();
		System.out.println();
		System.out.println(latest + " " + last_modified_file.getAbsolutePath());
		last_modified_file.delete();
	}

	/**
	 * 获得CPU使用率.
	 * 
	 * @return 返回cpu使用率
	 * @author GuoHuang
	 */
	private static double getCpuRatioForWindows() {
		try {
			String procCmd = "C:/Windows/System32/wbem/WMIC.exe"
					+ " process get Caption,CommandLine,"
					+ "KernelModeTime,ReadOperationCount,ThreadCount,UserModeTime,WriteOperationCount";
			// 取进程信息
			long[] c0 = readCpu(Runtime.getRuntime().exec(procCmd));
			Thread.sleep(30);
			long[] c1 = readCpu(Runtime.getRuntime().exec(procCmd));
			System.out.println(c0);
			System.out.println(c1);

			if (c0 != null && c1 != null) {
				System.out.println("(c0 != null && c1 != null)");
				long idletime = c1[0] - c0[0];
				long busytime = c1[1] - c0[1];
				return Double.valueOf(100 * (busytime) / (busytime + idletime))
						.doubleValue();
			} else {
				System.out.println("(c0 == null || c1 == null)");
				return 0.0;
			}
		} catch (Exception ex) {
			ex.printStackTrace();
			return 0.0;
		}
	}

	/**
	 * 
	 * 读取CPU信息.
	 * 
	 * @param proc
	 * @return
	 * @author GuoHuang
	 */
	private static long[] readCpu(final Process proc) {
		long[] retn = new long[2];
		try {
			proc.getOutputStream().close();
			InputStreamReader ir = new InputStreamReader(proc.getInputStream());
			LineNumberReader input = new LineNumberReader(ir);
			String line = input.readLine();
			System.out.println("readCpu()line:" + line);
			if (line == null) {
				return null;
			}
			int capidx = line.indexOf("Caption");
			int cmdidx = line.indexOf("CommandLine");
			int rocidx = line.indexOf("ReadOperationCount");
			int umtidx = line.indexOf("UserModeTime");
			int kmtidx = line.indexOf("KernelModeTime");
			int wocidx = line.indexOf("WriteOperationCount");
			long idletime = 0;
			long kneltime = 0;
			long usertime = 0;
			while ((line = input.readLine()) != null) {
				if (line.length() <= wocidx) {
					continue;
				}
				// 字段出现顺序：Caption,CommandLine,KernelModeTime,ReadOperationCount,
				// ThreadCount,UserModeTime,WriteOperation
				String caption = Bytes.substring(line, capidx, cmdidx - 1)
						.trim();
				String cmd = Bytes.substring(line, cmdidx, kmtidx - 1).trim();
				if (cmd.indexOf("wmic.exe") >= 0) {
					continue;
				}
				if (caption.equals("System Idle Process")
						|| caption.equals("System")) {
					idletime += Long.valueOf(
							Bytes.substring(line, kmtidx, rocidx - 1).trim())
							.longValue();
					idletime += Long.valueOf(
							Bytes.substring(line, umtidx, wocidx - 1).trim())
							.longValue();
					continue;
				}

				kneltime += Long.valueOf(
						Bytes.substring(line, kmtidx, rocidx - 1).trim())
						.longValue();
				usertime += Long.valueOf(
						Bytes.substring(line, umtidx, wocidx - 1).trim())
						.longValue();
			}
			retn[0] = idletime;
			retn[1] = kneltime + usertime;
			return retn;
		} catch (Exception ex) {
			ex.printStackTrace();
		} finally {
			try {
				proc.getInputStream().close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		return null;
	}
}
