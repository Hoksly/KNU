using System.Collections.Generic;

namespace  Instagram
{
    public class User
    {
        private string _username;
        private int _userId;
        private string _bio;
        private string _fullName;
        private bool _isPrivate;
    
        private List<int> _followers;
        private List<int> _followings;


        public User(string username, int userId, string bio, string fillName, bool isPrivate, List<int> followers, List<int> followings)
        {
            this._username = username;
            _userId = userId;
            this._bio = bio;
            _fullName = fillName;
            _isPrivate = isPrivate;
            this._followers = followers;
            this._followings = followings;
        }
    }    
}
