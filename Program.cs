using System;
using System.IO;
using System.IO.Compression;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;



namespace JNI
{

	class StackWrapper
	{
		[DllImport (@"libFirstLab.so", EntryPoint = "init")]
		public static extern IntPtr init();
		[DllImport (@"libFirstLab.so", EntryPoint = "push")]
		public static extern void push(IntPtr data, int data_size, IntPtr handler);
		[DllImport (@"libFirstLab.so", EntryPoint = "onTop")]
		public static extern IntPtr onTop(IntPtr handler);
		[DllImport (@"libFirstLab.so", EntryPoint = "topSize")]
		public static extern int topSize(IntPtr handler);
		[DllImport (@"libFirstLab.so", EntryPoint = "isEmpty")]
		public static extern bool isEmpty(IntPtr handler);
		[DllImport (@"libFirstLab.so", EntryPoint = "pop")]
		public static extern void pop(IntPtr handler);
		[DllImport (@"libFirstLab.so", EntryPoint = "cloneBuffer")]
		public static extern IntPtr cloneBuffer(IntPtr handler);
	}
	
	[Serializable]
	class Stack<T>
	{
	
		private IntPtr stack;
		
		public Stack()
		{
			this.stack = StackWrapper.init();
		}
		
		public void push(T data)
		{
			byte[] bytes = null;
			using (var baos = new MemoryStream ()) 
			{
				using (var ps = new StreamWriter (baos)) 
				{
					ps.Write (data);
					if(ps != null)
					{
						ps.Close ();
					}
				}
				bytes = baos.ToArray ();
			}
			StackWrapper.push(serialize(data), bytes.Length, this.stack);
		}
		
		public T onTop()
		{
			//Console.WriteLine("Size = " + StackWrapper.topSize(this.stack));
			return (T)deserialize(StackWrapper.onTop(this.stack), StackWrapper.topSize(this.stack));
		}
		
		public bool isEmpty()
		{
			return StackWrapper.isEmpty(this.stack);
		}
	    
		private IntPtr serialize(T data)
		{
			byte[] bytes = null;
			
			/*using (var baos = new MemoryStream ()) 
			{
				using (var ps = new StreamWriter (baos)) 
				{
					ps.Write (data);
					if(ps != null)
					{
						ps.Close ();
					}
				}
				bytes = baos.ToArray ();
			}*/
			
			BinaryFormatter formatter = new BinaryFormatter();
			var stream = new MemoryStream();
			formatter.Serialize(stream, data);
			bytes = stream.ToArray();
			
			IntPtr unmanagedPointer = Marshal.AllocHGlobal(bytes.Length);
			Marshal.Copy(bytes, 0, unmanagedPointer, bytes.Length);
			return unmanagedPointer;
		}
		
		private object deserialize(IntPtr ptr, int size)
		{
			byte[] bytes = new byte[size];
			Marshal.Copy(ptr, bytes, 0, size);
			Console.WriteLine(String.Join("", bytes));
			
			/*using (var baos = new MemoryStream (bytes)) 
			{
				baos.Seek(0, SeekOrigin.Begin);
				using (var ps = new StreamReader (baos)) 
				{
					return ps.Read ();
				}
			}*/
			
			/*BinaryFormatter formatter = new BinaryFormatter();
			MemoryStream ms = new MemoryStream(bytes);
			return formatter.Deserialize(ms);*/
						return null;
		}
	}

	class MainClass
	{ 
		public static void Main (string[] args)
		{
			Stack<int> stack = new Stack<int>();
			stack.push(777);
			Console.WriteLine(stack.onTop());
		}
	}
}
	