using System;
using System.IO;
using System.IO.Compression;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Xml.Serialization;



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
	class Stack<T> : ICloneable
	{
	
		private IntPtr stack;
		
		public Stack()
		{
			this.stack = StackWrapper.init();
		}
		
		public void push(T data)
		{
			byte[] bytes = null;
			
			bytes = serialize(data);
			
			StackWrapper.push(unmanagedBind(bytes), bytes.Length, this.stack);
		}
		
		public T onTop()
		{
			return (T)deserialize(StackWrapper.onTop(this.stack), StackWrapper.topSize(this.stack));
		}
		
		public bool isEmpty()
		{
			return StackWrapper.isEmpty(this.stack);
		}
		
		public void pop()
		{
			StackWrapper.pop(this.stack);
		}
		
		public void setStack(IntPtr stack)
		{
			this.stack = stack;
		}
		
		public object Clone()
		{
			Stack<T> obj = new Stack<T>();
			obj.setStack(StackWrapper.cloneBuffer(this.stack));
			
			return obj;
		}
		
		private byte[] serialize(T data)
		{
			byte[] bytes = null;
		
			BinaryFormatter bf = new BinaryFormatter();
			MemoryStream ms = new MemoryStream();
			bf.Serialize(ms, data);
			bytes = ms.ToArray();
			
			return bytes;
		}
	    
		private IntPtr unmanagedBind(byte[] bytes)
		{
			IntPtr unmanagedPointer = Marshal.AllocHGlobal(bytes.Length);
			Marshal.Copy(bytes, 0, unmanagedPointer, bytes.Length);
			return unmanagedPointer;
		}
		
		private object deserialize(IntPtr ptr, int size)
		{
			byte[] bytes = new byte[size];
			Marshal.Copy(ptr, bytes, 0, size);
			
 			MemoryStream memStream = new MemoryStream();
 			BinaryFormatter binForm = new BinaryFormatter();
 			memStream.Write(bytes, 0, bytes.Length);
 			memStream.Seek(0, SeekOrigin.Begin);
 			object obj = (object) binForm.Deserialize(memStream);
			
			return obj;
		}
	}

	class MainClass
	{ 
		public static void Main (string[] args)
		{
			Stack<int> stack = new Stack<int>();
			stack.push(7778);
			stack.push(1);
			stack.push(2);
			Console.WriteLine(stack.onTop());
		}
	}
}
	