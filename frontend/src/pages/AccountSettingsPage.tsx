import { Link } from "react-router-dom";
import AccountSettings from "../components/AccountSettings";
import NavBar from "../components/NavBar";

const AccountSettingsPage = () => {
  return (
    <>
      <NavBar>
        <Link className="link" to="/">
          Sign in
        </Link>
        <Link className="link" to="/control">
          Control
        </Link>
      </NavBar>
      <AccountSettings />
    </>
  );
};

export default AccountSettingsPage;
