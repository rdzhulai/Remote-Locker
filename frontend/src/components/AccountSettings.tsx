import { useContext } from "react";
import StateContext from "../state/StateContext";
import { Field, Formik } from "formik";

interface AccountSettingsValuesType {
  name: string;
  password: string;
  newUserName: string;
  newUserPassword: string;
  newUserAdmin: boolean;
}
const initialValues: AccountSettingsValuesType = {
  name: "",
  password: "",
  newUserName: "",
  newUserPassword: "",
  newUserAdmin: false,
};
const AccountSettings = () => {
  // const { state } = useContext(StateContext);
  // const onSubmit = async (values: AccountSettingsValuesType) => {
  //   console.log(values);
  // };
  return <div className="form-panel">Account Settings</div>;
};

export default AccountSettings;

// {/* <Formik initialValues={initialValues} onSubmit={onSubmit}>
//         <div className="flex">
//           {/* <div>{state?.user?.name ?? ""}</div> */}
//     <button type="button">Change name</button>
//   </div>
//   <div className="flex">
//     <div>{state?.user?.password ?? ""}</div>
//     <button type="button">Change pasword</button>
//   </div>
//   <div></div>
//   <div>
//     <Field className="btn-submit" type="submit">
//       Submit
//     </Field>
//   </div>
// </Formik >
