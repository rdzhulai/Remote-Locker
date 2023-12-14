import { Field, Formik, FormikHelpers } from "formik";
import { useContext, useState } from "react";
import { useNavigate } from 'react-router-dom';
import StateContext from "../state/StateContext";
import { Actions } from "../types/state";

interface SignInFormValuesType {
  name: string;
  password: string;
}

const initialValues: SignInFormValuesType = {
  name: "",
  password: "",
};

const SignInForm = () => {
  const [SignInStatus, setSignInStatus] = useState("");
  const navigate = useNavigate();
  const { state, dispatch } = useContext(StateContext);
  const onSubmit = async (
    { name, password }: SignInFormValuesType,
    helpers: FormikHelpers<SignInFormValuesType>
  ) => {
    const response = await fetch(`${process.env.REACT_APP_BACKEND}/signin`, {
      method: "POST", headers: {
        'Content-Type': 'application/json',
      }, body: JSON.stringify({ "name": name, "password": password })
    }
    );
    const data = await response.json();
    if (response.ok) {
      dispatch({ type: Actions.SignInAccount, payload: data });
      setSignInStatus("You are already signed in.");
      navigate('/control');
    } else {
    }
    helpers.setValues({
      name: '', password: ''
    })
  };
  return (
    <div className="form-panel">
      <Formik initialValues={initialValues} onSubmit={onSubmit} t>
        {(formik) => (
          <form onSubmit={formik.handleSubmit}>
            <div className="form-section">
              <label htmlFor="username">Username</label>
              <Field
                className="text-field"
                type="text"
                name="name"
                id="username"
                required
              />
            </div>
            <div className="form-section mt-1">
              <label className="" htmlFor="password">Password</label>
              <Field
                className="text-field"
                type="password" name="password" id="password" required
              ></Field>
            </div>
            {SignInStatus && <h2 className="mt-3 text-center">{SignInStatus}</h2>}
            <div className="text-center">
              <button
                className="btn-submit"
                type="submit"
              >
                Sign in
              </button>
            </div>
          </form>
        )}
      </Formik>
    </div>
  );
};

export default SignInForm;
