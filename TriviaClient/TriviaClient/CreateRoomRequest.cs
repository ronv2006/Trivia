using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    public class CreateRoomRequest
    {
        public String Name { get; set; }
        public String AnswerTimeout { get; set; }
        public String MaxUsers { get; set; }
        public String QuestionCount { get; set; }

    }
}
