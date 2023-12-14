import { Link } from "react-router-dom";
import LockerPanel from "../components/LockerPanel";
import NavBar from "../components/NavBar";

const ControlPage = () => {
  return (
    <>
      <NavBar>
        <Link className="link" to="/">
          Sign in
        </Link>
        <Link className="link" to="/settings">
          Settings
        </Link>
      </NavBar>
      <LockerPanel />
    </>
  );
};

export default ControlPage;
