using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
using System.Threading;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for JoinRoomPage.xaml
    /// </summary>
    public partial class JoinRoomPage : Page
    {
        private Thread updateThread;
        private bool isRunning = true;
        private String username;
        public JoinRoomPage(String username)
        {


            InitializeComponent();

            updateThread = new Thread(new ThreadStart(ShowCurrentActiveRooms));
            this.username = username;

            updateThread.Start();




        }

        void JoinRoom_Click(Object sender, RoutedEventArgs e)
        {
           

            // Wait for the update thread to finish gracefully
            
            
            Button bSender = (Button)sender;
            JoinRoomRequest request = new JoinRoomRequest();
            request.RoomName = bSender.Content.ToString();


            StatusResponse response = Communicator.JoinRoom(request);
            if(response.Status == 1)
            {
                isRunning = false;
                updateThread.Join();
                NavigationService.Navigate(new RoomMemberPage(bSender.Content.ToString(), username));
            }
            else
            {
                string messageBoxText = "Room full";
                string caption = "Join Room Error";
                MessageBoxButton button = MessageBoxButton.OK;
                MessageBoxImage icon = MessageBoxImage.Warning;
                MessageBoxResult result;

                result = MessageBox.Show(messageBoxText, caption, button, icon, MessageBoxResult.Yes);
            }
            

        }

        public void ShowCurrentActiveRooms()

        {

            while (isRunning)
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                        bool isEmpty = false;
                        String roomsString = Communicator.GetRooms().Rooms;
                        String[] rooms = roomsString.Split(",");
                        StackPanel stack = new StackPanel();
                        for(int i = 0; i < rooms.Length; i++)
                        {
                            Button roomButton = new Button();
                        roomButton.Click += JoinRoom_Click;
                            roomButton.Content = rooms[i];
                            if (rooms[i] == "")
                            {
                            isEmpty = true;
                            }
                            stack.Children.Add(roomButton);
                        }
                    if (isEmpty == true)
                    {
                        RoomsScroll.Content = "";
                    }
                    else
                    {
                        RoomsScroll.Content = stack;
                    }


                    

                });
                System.Threading.Thread.Sleep(1000);
            }
        }




            void Go_back_click(Object sender, RoutedEventArgs e)
            {
                isRunning = false;

                
                updateThread.Join();
                NavigationService.Navigate(new MainMenuPage(this.username));


            }

            void Exit_click(Object sender, RoutedEventArgs e)
            {
                isRunning = false;  
                Communicator.Logout();
                MainWindow mainWindow = Application.Current.MainWindow as MainWindow;
                mainWindow.Close();

            }
        
    }
    }

    

