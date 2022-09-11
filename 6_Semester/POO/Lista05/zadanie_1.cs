using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Net.Mail;
using System.Net.Mime;

namespace POO_Lista5
{
    class SmtpFacade
    {
        public void Send(string From, string To,
        string Subject, string Body,
        Stream Attachment, string AttachmentMimeType)
        {
            MailMessage message = new MailMessage(From, To, Subject, Body);
            
            if (Attachment != null)
            {
                message.Attachments.Add(new Attachment(Attachment, AttachmentMimeType);
            }

            var c = new SmtpClient(/* Port, Credentails, SSL etc.*/);

            try
            {
                c.Send(message);
            }
            catch (Exception e)
            {
                Console.Error.WriteLine("Exception: " + e);
            }
            message.Dispose();
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            SmtpFacade email_sender = new SmtpFacade();
            //email_sender.Send();
        }
    }
}
