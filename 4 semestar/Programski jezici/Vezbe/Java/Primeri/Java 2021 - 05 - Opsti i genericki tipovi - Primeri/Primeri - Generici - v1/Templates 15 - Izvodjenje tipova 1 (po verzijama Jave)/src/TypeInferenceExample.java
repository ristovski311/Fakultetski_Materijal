import java.util.ArrayList;  
import java.util.List;  

public class TypeInferenceExample {
	
	public static void showList(List<Integer>list)
	{
		if(!list.isEmpty())
		{  
			list.forEach(System.out::println);
        }
		else
			System.out.println("list is empty");

	}
}
