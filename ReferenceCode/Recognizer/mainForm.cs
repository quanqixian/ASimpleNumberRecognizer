using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

namespace Recognizer
{
	/// <summary>
	/// Form1 的摘要说明。
	/// </summary>
	public class mainForm : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Label input;
		private System.Windows.Forms.ComboBox objective;
		private System.Windows.Forms.Button study;
		private System.Windows.Forms.Button clean;
		private System.ComponentModel.Container components = null;
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		
		private Position   pos;
		private LinkList   list;
		private LinkList[] data;
		private int[]      array;
		private int        item_1;
		private int        item_2;
		private bool       down;
		private System.Windows.Forms.Button begin;
        private System.Windows.Forms.Label noticeLabel;
		private Database   database;

		public mainForm()
		{
			//
			// Windows 窗体设计器支持所必需的
			//
			InitializeComponent();

			//
			// TODO: 在 InitializeComponent 调用后添加任何构造函数代码
			//

			list     = new LinkList();
			database = new Database();
			data     = database.getData();
			down     = false;

			objective.SelectedIndex = 0;
			
		}

		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		protected override void OnPaint(PaintEventArgs e)
		{
			base.OnPaint(e);

			Graphics graphic = this.CreateGraphics();

			graphic.Clear(SystemColors.Control);

			list.clear();
	
		}
		#region Windows 窗体设计器生成的代码
		/// <summary>
		/// 设计器支持所需的方法 - 不要使用代码编辑器修改
		/// 此方法的内容。
		/// </summary>
		private void InitializeComponent()
		{
            this.input = new System.Windows.Forms.Label();
            this.objective = new System.Windows.Forms.ComboBox();
            this.study = new System.Windows.Forms.Button();
            this.begin = new System.Windows.Forms.Button();
            this.clean = new System.Windows.Forms.Button();
            this.noticeLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // input
            // 
            this.input.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.input.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.input.Font = new System.Drawing.Font("Arial Black", 72F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.input.Location = new System.Drawing.Point(31, 62);
            this.input.Name = "input";
            this.input.Size = new System.Drawing.Size(112, 144);
            this.input.TabIndex = 1;
            this.input.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // objective
            // 
            this.objective.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.objective.Items.AddRange(new object[] {
            "0",
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9"});
            this.objective.Location = new System.Drawing.Point(100, 246);
            this.objective.MaxDropDownItems = 10;
            this.objective.Name = "objective";
            this.objective.Size = new System.Drawing.Size(72, 20);
            this.objective.TabIndex = 2;
            // 
            // study
            // 
            this.study.Location = new System.Drawing.Point(12, 243);
            this.study.Name = "study";
            this.study.Size = new System.Drawing.Size(72, 24);
            this.study.TabIndex = 4;
            this.study.Text = "学习";
            this.study.Click += new System.EventHandler(this.study_Click);
            // 
            // begin
            // 
            this.begin.Location = new System.Drawing.Point(238, 243);
            this.begin.Name = "begin";
            this.begin.Size = new System.Drawing.Size(72, 24);
            this.begin.TabIndex = 0;
            this.begin.Text = "识别";
            this.begin.Click += new System.EventHandler(this.recognize_Click);
            // 
            // clean
            // 
            this.clean.Location = new System.Drawing.Point(326, 243);
            this.clean.Name = "clean";
            this.clean.Size = new System.Drawing.Size(72, 24);
            this.clean.TabIndex = 6;
            this.clean.Text = "清屏";
            this.clean.Click += new System.EventHandler(this.clean_Click);
            // 
            // noticeLabel
            // 
            this.noticeLabel.AutoSize = true;
            this.noticeLabel.Location = new System.Drawing.Point(48, 16);
            this.noticeLabel.Name = "noticeLabel";
            this.noticeLabel.Size = new System.Drawing.Size(317, 12);
            this.noticeLabel.TabIndex = 7;
            this.noticeLabel.Text = "请在屏幕空白处用鼠标输入0--9中的某一个数字进行识别！";
            // 
            // mainForm
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(6, 14);
            this.ClientSize = new System.Drawing.Size(410, 295);
            this.Controls.Add(this.noticeLabel);
            this.Controls.Add(this.clean);
            this.Controls.Add(this.begin);
            this.Controls.Add(this.study);
            this.Controls.Add(this.objective);
            this.Controls.Add(this.input);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "mainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "0 - 9手写体识别系统 Demo [D.T.Software]";
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.mainForm_MouseDown);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.mainForm_MouseMove);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.mainForm_MouseUp);
            this.ResumeLayout(false);
            this.PerformLayout();

		}
		#endregion

		/// <summary>
		/// 应用程序的主入口点。
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new mainForm());
		}

		private void characteristic()
		{
			int count;
			int maxX;
			int maxY;
			int minX;
			int minY;
			int x1;
			int y1;
			int x2;
			int y2;
			int dx;
			int dy;

			list.gotoFirst();

			count = list.length();
			pos   = (Position)list.nextItem();
			maxX  = pos.x;
			maxY  = pos.y;
			minX  = pos.x;
			minY  = pos.y;

			while((pos=(Position)list.nextItem())!=null)
			{
				if(maxX<pos.x)
				{
					maxX = pos.x;
				}

				if(maxY<pos.y)
				{
					maxY = pos.y;
				}

				if(minX>pos.x)
				{
					minX = pos.x;
				}

				if(minY>pos.y)
				{
					minY = pos.y;
				}
			}

			dx = (maxX - minX)/3;
			dy = (maxY - minY)/3;
			x1 = minX  + dx;
			y1 = minY  + dy;
			x2 = x1    + dx;
			y2 = y1    + dy;

			array = new int[9];

			for(int i=0; i<9; i++)
			{
				array[i] = 0;
			}

			list.gotoFirst();

			while((pos=(Position)list.nextItem())!=null)
			{
				if(pos.x>=minX && pos.x<x1 && pos.y>=minY && pos.y<y1)
				{
					array[0]++;
				}

				if(pos.x>=x1 && pos.x<x2 && pos.y>=minY && pos.y<y1)
				{
					array[1]++;
				}

				if(pos.x>=x2 && pos.x<=maxX && pos.y>=minY && pos.y<y1)
				{
					array[2]++;
				}

				if(pos.x>=minX && pos.x<x1 && pos.y>=y1 && pos.y<y2)
				{
					array[3]++;
				}

				if(pos.x>=x1 && pos.x<x2 && pos.y>=y1 && pos.y<y2)
				{
					array[4]++;
				}

				if(pos.x>=x2 && pos.x<maxX && pos.y>=y1 && pos.y<y2)
				{
					array[5]++;
				}

				if(pos.x>=minX && pos.x<x1 && pos.y>=y2 && pos.y<=maxY)
				{
					array[6]++;
				}

				if(pos.x>=x1 && pos.x<x2 && pos.y>=y2 && pos.y<=maxY)
				{
					array[7]++;
				}

				if(pos.x>=x2 && pos.x<=maxX && pos.y>=y2 && pos.y<=maxY)
				{
					array[8]++;
				}
			}

			for(int i=0; i<9; i++)
			{
				array[i] *= 100;
				array[i] /= count;
			}

		}

		private void recognize()
		{
			double   xxx    = Int32.MaxValue;
			double   sum    = 0;
			int[]    temp;
			LinkList slider;

			for(int i=0; i<10; i++)
			{
				slider = data[i];

				slider.gotoFirst();

				while((temp=(int[])slider.nextItem())!=null)
				{
					sum = 0;

					for(int j=0; j<9; j++)
					{
						sum += (array[j]-temp[j])*(array[j]-temp[j]);
					}

						sum = Math.Sqrt(sum);

						if(sum<xxx)
						{
							item_2 = item_1;
							xxx    = sum;
							item_1 = i;
						}
				}
			}
		}

		private void mainForm_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
		{
			if(down==true)
			{
				Position tempPos = new Position();
				Pen      pen     = new Pen(Color.Black);
				Graphics graphic = this.CreateGraphics();

				graphic.DrawLine(pen,pos.x,pos.y,e.X,e.Y);

				pos   = new Position();
				pos.x = e.X;
				pos.y = e.Y;

				tempPos.x = e.X;
				tempPos.y = e.Y;

				list.addLast(tempPos);

				study.Enabled = true;
			}
		}

		private void mainForm_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
		{
			Position tempPos = new Position();
 
			down = true;

			pos   = new Position();
			pos.x = e.X;
			pos.y = e.Y;

			tempPos.x = e.X;
			tempPos.y = e.Y;

			list.addLast(tempPos);

		}

		private void mainForm_MouseUp(object sender, System.Windows.Forms.MouseEventArgs e)
		{
			down = false;
		}

		private void clean_Click(object sender, System.EventArgs e)
		{
			Graphics graphic = this.CreateGraphics();

			graphic.Clear(SystemColors.Control);

			list.clear();

			input.Text = "";
		}

		private void recognize_Click(object sender, System.EventArgs e)
		{
			object o;

			if(list.isEmpty())
			{
				MessageBox.Show(this,"请先写入您要识别的数字！","注意");
				return;
			}

			characteristic();
			recognize();

			o = item_1;
			input.Text = o.ToString();
		}

		private void study_Click(object sender, System.EventArgs e)
		{
			object o   = objective.SelectedIndex;
			int    num = objective.SelectedIndex;

			characteristic();

			DialogResult result = MessageBox.Show(this,"学习数字 "+o.ToString()+" ？","请确认",MessageBoxButtons.YesNo);

			if(result==DialogResult.Yes)
			{
				database.addData(array,num);

				data[num].addLast(array);

				MessageBox.Show(this,"学习成功！","提示");
			}
		}

	}
}
