
import javax.swing.*;

class IncrementSlider extends JSlider {
    public IncrementSlider() {
        super(0,10000);
    }

    synchronized public void Increase(int increment){
        if(0 < getValue() + increment && getValue() + increment < 10000) {
            setValue((int)getValue() + increment);
        }
    }
}


class CustomThread extends Thread implements IncrementThread{
    private int increment;
    private IncrementSlider mySlider;
    private int count;
    private static int DelayBound = 100000; // used for delay
    private static int THREAD_COUNTER = 0;
    private int curNum;

    public CustomThread(IncrementSlider mySlider, int increment, int priority) {
        this.mySlider = mySlider;
        this.increment = increment;
        curNum = ++THREAD_COUNTER;
        setPriority(priority);
    }

    @Override
    public void run() {
        while(!interrupted()){
            int val = (int)(mySlider.getValue());
            ++count;
            if(count > DelayBound){
                mySlider.Increase(increment);
                count = 0;
            }
        }
    }

    public JPanel GetJPanel() {
        JPanel panel = new JPanel();
        JLabel label = new JLabel("Thread #" + curNum + ", Increment = " + increment);
        SpinnerModel sModel = new SpinnerNumberModel(getPriority(), Thread.MIN_PRIORITY, Thread.MAX_PRIORITY, 1);
        JSpinner Spinner = new JSpinner(sModel);
        Spinner.addChangeListener(e->{setPriority((int)(Spinner.getValue()));});
        panel.add(label);
        panel.add(Spinner);
        return panel;
    }
}

public class TaskA {
    public void run() {
        JFrame MainFrame = new JFrame();
        MainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        MainFrame.setSize(600, 750);
        IncrementSlider mySSlider = new IncrementSlider();

        CustomThread Tthread1 = new CustomThread(mySSlider, +1, Thread.NORM_PRIORITY);
        CustomThread TThread2 = new CustomThread(mySSlider, -1, Thread.NORM_PRIORITY);

        JButton startBTTN = new JButton("ПУСК");
        startBTTN.addActionListener(e -> {
            Tthread1.start();
            TThread2.start();
            startBTTN.setEnabled(false);
        });
        JPanel MainFramePanel = new JPanel();
        MainFramePanel.setLayout(new BoxLayout(MainFramePanel, BoxLayout.Y_AXIS));

        MainFramePanel.add(Tthread1.GetJPanel());
        MainFramePanel.add(TThread2.GetJPanel());
        MainFramePanel.add(mySSlider);

        JPanel jPanel = new JPanel();
        jPanel.add(startBTTN);
        MainFramePanel.add(jPanel);

        MainFrame.setContentPane(MainFramePanel);
        MainFrame.setVisible(true);
    }
}
