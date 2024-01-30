using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    public class StatusResponse
    {
        public int Status { get; set; }

        public StatusResponse(int Status)
        {
            this.Status = Status;
        }
    }
}
