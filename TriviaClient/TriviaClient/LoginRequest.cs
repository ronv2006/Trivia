using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace TriviaClient
{
    public class LoginRequest
    {
        public string Username { get; private set; }
        public string Password { get; private set; }

        public LoginRequest(string username, string password)
        {
            Username = username;
            Password = password;
        }
    }
}
