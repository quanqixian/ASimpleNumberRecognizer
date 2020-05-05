using System;
using System.Data;
using System.Data.OleDb;

namespace Recognizer
{
	/// <summary>
	/// kernel 的摘要说明。
	/// </summary>
	class LinkList
	{
		private class Node
		{
			public object item;
			public Node   next;
		}
	
		private Node head;
		private Node tail;
		private Node slider;
		private int  count;
	
		public LinkList()
		{
			clear();
		}
	
		public void clear()
		{
			head   = null;
			tail   = null;
			slider = null;
			count  = 0;		
		}
	
		public bool isEmpty()
		{
			return head==null;	  
		}
	
		public void gotoFirst()
		{
			slider = head;
		}

		public object nextItem()
		{
			if(slider==null)
			{
				return null;
			}

			object o = slider.item;

			slider = slider.next;

			return o;
		}

		public object getFirst()
		{
			return head.item;
		}
	
		public object getAt(int index)
		{
			if(index<1 && index>count)
			{
				return null;
			}
	    
			Node g  = head;
		
			for(int i=1; i<index; i++)
				g  = g.next;
		    	
			return g.item; 
		      
		}
	
		public void addAt(object item,int index)
		{
			Node g  = head;
			Node ag = head;
		
			if(index<1)
			{
				addFirst(item);
			}
			else
				if(index>count)
			{
				addLast(item);
			}
			else
			{
				for(int i=1; i<index; i++)
				{
					if(g==ag)
					{
						g  = g.next;
					}
					else
					{ 
						ag = g;
						g  = g.next;
					} 
				}
			
				if(index==1)
				{
					head      = new Node();
					head.item = item;
					head.next = g;
				}
				else
				{
					ag         = new Node();
					ag.item    = item;
					ag.next    = g;
				}
			
				count++;
			}
		}
	
		public object removeAt(int index)
		{
			if(index<1 && index>count)
			{
				return null;
			}
	    
			Node g  = head;
			Node ag = head;
		
			for(int i=1; i<index; i++)
			{
				if(g==ag)
				{
					g  = g.next;
				}
				else
				{ 
					ag = g;
					g  = g.next;
				} 
			}
		  
			if(index==1)
			{
				head = head.next;
			}
			else
			{
				ag.next = g.next;
			}
		  
			count--;
		  
			return g.item;
		}
	
		public void addFirst(object item)
		{
			Node g    = head;
		
			head      = new Node();
			head.item = item;
			head.next = g;
		
			count++;
		}
	
		public void addLast(object item)
		{
			if(head==null)
			{
				head      = new Node();
				head.next = null;
				head.item = item;
				tail      = head;
			}
			else
			{
				tail.next = new Node();
				tail      = tail.next;
				tail.next = null;
				tail.item = item;
			}
	   
			count++;
		}
	
		public int length()
		{
			return count;
		}
	
		public object removeFirst()
		{
			if(head==null)
			{
				return null;
			}

			Node temp = head;
			head      = head.next;
		
			count--;
		
			return temp.item;
		}
	}

	class Position
	{
		public int x = 0;
		public int y = 0;
	}

	class Database
	{
		private string           driver;
		private LinkList[]       data;
		private OleDbConnection  connect;
		private OleDbDataAdapter adapter;
		private OleDbCommand     command;
		private OleDbTransaction myTrans;
		private DataSet          dataSet;
		private DataTable        table;

		public Database()
		{
			driver   = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source ="+"database.mdb"+";User ID=;Password=;";
		}

		public void addData(int[] array , int num)
		{
			object o   = num;
			string sql = "INSERT INTO " + o.ToString() + " VALUES (";

			o = array[0];

			sql += o.ToString();

			for(int i=1; i<9; i++)
			{
				o = array[i];

				sql += "," + o.ToString();
			}

			sql += ")";

			connect = new OleDbConnection(driver);
			connect.Open();
			command = new OleDbCommand("",connect);
			myTrans = connect.BeginTransaction();
			command.Transaction = myTrans;
			command.CommandText = sql;
			command.ExecuteNonQuery();
			myTrans.Commit();
			connect.Close();
		}

		public LinkList[] getData()
		{
			string sql = "SELECT * FROM ";
			int[]  array;
			object o;

			data    = new LinkList[10];
			connect = new OleDbConnection(driver);

			for(int i=0; i<10; i++)
			{
				o = i;

				data[i] = new LinkList();
				adapter = new OleDbDataAdapter(sql+o.ToString(),connect);
				dataSet = new DataSet();

				adapter.Fill(dataSet);

				table = dataSet.Tables[0];

				for(int j=0; j<table.Rows.Count; j++)
				{
					array = new int[9];

					for(int k=0; k<9; k++)
					{
						array[k] = (int)table.Rows[j].ItemArray[k];
					}

					data[i].addLast(array);
				}
			}

			connect.Close();

			return data;
		}
	}
}
