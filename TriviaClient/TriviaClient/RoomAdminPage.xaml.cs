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
using System.Threading;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for RoomAdminPage.xaml
    /// </summary>
    public partial class RoomAdminPage : Page
    {
        private Thread showPlayersThread;
        private bool isRunning = true;
        private int roomId;
        String username;
        public RoomAdminPage(String roomName, String username)
        {
            this.roomId = roomId;
            this.username = username;
            InitializeComponent();
            NameRoomBlock.Text = NameRoomBlock.Text + " " + roomName;
            showPlayersThread = new Thread(new ThreadStart(ShowCurrentActiveRooms));


            showPlayersThread.Start();



        }

        public void CloseRoom_Click(Object sender, RoutedEventArgs e)
        {
            isRunning = false;
            showPlayersThread.Join();
            Communicator.CloseRoom();

            NavigationService.Navigate(new JoinRoomPage(this.username));
        }

        

        public void ShowCurrentActiveRooms()

        {

            while (isRunning)
            {
                
                Application.Current.Dispatcher.Invoke(() =>
                {
                    PlayersScroll.Content = "";
                    GetRoomStateResponse response = Communicator.GetRoomState();
                    String[] players = response.Players.Split(",");
                    for (int i = players.Length - 1; i >= 0; i--){


                        PlayersScroll.Content = PlayersScroll.Content + "\n" + players[i];
                    }
                    

                    




                });
                System.Threading.Thread.Sleep(1000);
            }
        }
    }
}
