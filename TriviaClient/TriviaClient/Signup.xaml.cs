using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for Signup.xaml
    /// </summary>
    public partial class Signup : Page
    {
        public Signup()
        {
            
            InitializeComponent();
        }

        void Gop_back_click(Object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new MenuPage());

        }

        void Exit_click(Object sender, RoutedEventArgs e)
        {
            MainWindow mainWindow = Application.Current.MainWindow as MainWindow;
            mainWindow.Close();

        }

        void Signup_Click(Object sender, RoutedEventArgs e)
        {
            String username = usernameBlock.Text;
            String password = passwordBlock.Text;
            String email = emailBlock.Text;
            if (username.Length <= 0 || password.Length <= 0 || email.Length <= 0)
            {
                return;
            }
            StatusResponse response = Communicator.Signup(username, password, email);
            if (response.Status == 0)
            {
                string messageBoxText = "Username already exists";
                string caption = "Signup Failed";
                MessageBoxButton button = MessageBoxButton.OK;
                MessageBoxImage icon = MessageBoxImage.Warning;
                MessageBoxResult result;

                result = MessageBox.Show(messageBoxText, caption, button, icon, MessageBoxResult.Yes);

            }
            else
            {
                NavigationService.Navigate(new MainMenuPage(username));
            }

        }
    }
}

