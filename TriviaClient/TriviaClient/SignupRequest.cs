using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    public class SignupRequest
    {
        public String Username { get; set; }
        public String Password { get; set; }
        public String Email { get; set; }
        public SignupRequest(String Username, String Password, String Email)
        {
            this.Username = Username;
            this.Password = Password;
            this.Email = Email;
        }
    }
}
