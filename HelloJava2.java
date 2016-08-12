import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
public class HelloJava2{
	public static void main(String[] args){
		JFrame frame=new JFrame("HelloJava2");
		HelloJava2 temp=new HelloJava2();
		frame.add(temp.new HelloComponent2("Hello Java!"));
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(300,300);
		frame.setVisible(true);
	}
	class HelloComponent2 extends JComponent implements MouseMotionListener{
		String theMessage;
		int mouseX=0,mouseY=0;
		public HelloComponent2(String message){
			theMessage=message;
			addMouseMotionListener(this);
		}
		public void paintComponent(Graphics g){
			g.drawString(theMessage,mouseX+10,mouseY+20);
		}
		public void mouseDragged(MouseEvent e){
			mouseX=e.getX();
			mouseY=e.getY();
			repaint();
		}
		public void mouseMoved(MouseEvent e){}
	}
}