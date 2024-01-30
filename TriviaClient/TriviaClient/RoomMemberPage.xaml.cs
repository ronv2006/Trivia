using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
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
    /// Interaction logic for RoomMemberPage.xaml
    /// </summary>
    public partial class RoomMemberPage : Page
    {
        private Thread showPlayersThread;
        private bool isRunning = true;
        private int roomId;
        String username;
        public RoomMemberPage(String roomName, String username)
        {
            this.roomId = roomId;
            this.username = username;
            InitializeComponent();
            NameRoomBlock.Text = NameRoomBlock.Text + " " + roomName;
            showPlayersThread = new Thread(new ThreadStart(ShowCurrentActiveRooms));


            showPlayersThread.Start();

        }

        void LeaveRoom_Click(Object sender, RoutedEventArgs e)
        {
            
            isRunning = false;
            showPlayersThread.Join();
            Communicator.LeaveRoom();
            Application.Current.Dispatcher.Invoke(() =>
            {
                NavigationService.Navigate(new JoinRoomPage(username));
            });

        }

        public void LeaveRoom()
        {
            isRunning = false;

            Application.Current.Dispatcher.Invoke(() =>
            {
                NavigationService.Navigate(new JoinRoomPage(username));
            });


        }

        public void ShowCurrentActiveRooms()

        {
            GetRoomStateResponse response = new GetRoomStateResponse();
            bool leaveRoom = false;
            while (isRunning)
            {

                Application.Current.Dispatcher.Invoke(() =>
                {
                    PlayersScroll.Content = "";
                    GetRoomStateResponse response = Communicator.GetRoomState();
                    String[] players = response.Players.Split(",");
                    for (int i = players.Length - 1; i >= 0; i--)
                    {


                        PlayersScroll.Content = PlayersScroll.Content + "\n" + players[i];
                    }

                    if (response.Status == 42)
                    {
                        isRunning = false;
                        leaveRoom = true;
                        
                    }

                    
                });
                System.Threading.Thread.Sleep(1000);
            }
            if(leaveRoom)
            {
                LeaveRoom();
            }
            
        }

        
    }
}

