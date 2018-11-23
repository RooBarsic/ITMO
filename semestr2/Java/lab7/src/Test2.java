import javax.swing.SwingUtilities;
import javax.swing.JPanel;
import javax.swing.JFrame;
import java.awt.FlowLayout;
import javax.swing.JLabel;
import javax.swing.JSlider;
import java.awt.Font;
import java.awt.Color;

public class Test2 extends JFrame {

    private static final long serialVersionUID = 1L;
    private JPanel jContentPane = null;
    private JLabel jLabel = null;
    private JSlider jSlider = null;

    private JSlider getJSlider() {
        if (jSlider == null) {
            jSlider = new JSlider(0,255,255);
            jSlider.addChangeListener(new javax.swing.event.ChangeListener() {
                public void stateChanged(javax.swing.event.ChangeEvent e) {
                    jLabel.setForeground(new Color(0,0,0,jSlider.getValue()));				}
            });
        }
        return jSlider;
    }
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                Test2 thisClass = new Test2();
                thisClass.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                thisClass.setVisible(true);
            }
        });
    }
    public Test2() {
        super();
        initialize();
    }
    private void initialize() {
        this.setSize(473, 200);
        this.setContentPane(getJContentPane());
        this.setTitle("JFrame");
    }

    private JPanel getJContentPane() {
        if (jContentPane == null) {
            jLabel = new JLabel();
            jLabel.setText("Ура!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
            jLabel.setFont(new Font("Arial", Font.BOLD, 36));
            jLabel.setForeground(Color.black);
            jLabel.setEnabled(true);
            jContentPane = new JPanel();
            jContentPane.setLayout(new FlowLayout());
            jContentPane.add(jLabel, null);
            jContentPane.add(getJSlider(), null);
        }
        return jContentPane;
    }
}  //  @jve:decl-index=0:visual-constraint="37,38"
