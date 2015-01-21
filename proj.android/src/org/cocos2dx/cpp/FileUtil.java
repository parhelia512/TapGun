
package Project.TapGun.Sasebon.minaka;

import java.io.File;
import java.io.IOException;

public class FileUtil
{
	public static String getExternalStorageDirectory()
	{
		File readFile = new File("Graph");
		String s="";
		//s = readFile.getAbsolutePath();
		//s = readFile.getPath();
		s = System.getProperty("Graph");
		return(s);
		/*
		try
		{
			File readFile = new File("Graph");
			String s="";
			s = readFile.getCanonicalPath();
			return(s);
		}
		catch ( IOException e)
		{
			return ("");
		}*/
	}
}
