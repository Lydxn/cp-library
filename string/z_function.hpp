vector<int> z_function(string s) {
  int n = s.size();
  vector<int> z(n);
  for (int i = 1; i < n; i++) {
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i] += 1;
    }
  }
  return z;
}
