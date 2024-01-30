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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for CreateRoomPage.xaml
    /// </summary>
    public partial class CreateRoomPage : Page
    {
        String username;
        public CreateRoomPage(String username)
        {
           this.username = username;
            InitializeComponent();
        }
        void Go_back_click(Object sender, RoutedEventArgs e)
        {
            NavigationService.GoBack();




        }
        void Exit_click(Object sender, RoutedEventArgs e)
        {
            MainWindow mainWindow = Application.Current.MainWindow as MainWindow;
            mainWindow.Close();

        }

        void CreateRoom_Click(Object sender, RoutedEventArgs e)
        {
            if(RoomNameBlock.Text.Length <= 0)
            {
                return;
            }
            CreateRoomRequest roomRequest = new CreateRoomRequest();
            roomRequest.Name = RoomNameBlock.Text;
            roomRequest.AnswerTimeout = AnswerTimeoutSlider.Value.ToString();
            roomRequest.MaxUsers = MaxUsersSlider.Value.ToString();
            roomRequest.QuestionCount = QuestionCountSlider.Value.ToString();
            StatusResponse response = Communicator.CreateRoom(roomRequest);
            if(response.Status == 0)
            {
                string messageBoxText = "Room with this name already exists";
                string caption = "Create Room Failed";
                MessageBoxButton button = MessageBoxButton.OK;
                MessageBoxImage icon = MessageBoxImage.Warning;
                MessageBoxResult result;

                result = MessageBox.Show(messageBoxText, caption, button, icon, MessageBoxResult.Yes);
            }
            else
            {
                
                NavigationService.Navigate(new RoomAdminPage(roomRequest.Name, username));
            }

        }

    }
}
