using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    public class GetRoomStateResponse
    {
        public int Status { get; set; }
        public int QuestionCount { get; set; }
        public bool HasGameBegun { get; set; }
        public String Players { get; set; }
        public float AnswertTimeout { get; set; }
    }
}
