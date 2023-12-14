import { Link } from "react-router-dom";
import NavBar from "../components/NavBar";
import SignInForm from "../components/SignInForm";
import { useContext } from "react";
import StateContext from "../state/StateContext";

const SignInPage = () => {
  const { state } = useContext(StateContext);
  return (
    <>
      {state?.user && (
        <NavBar>
          <Link className="link" to="/control">
            Control
          </Link>
          <Link className="link" to="/settings">
            Settings
          </Link>
        </NavBar>
      )}

      <SignInForm />
    </>
  );
};

export default SignInPage;
