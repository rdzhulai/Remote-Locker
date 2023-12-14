import { Field, Formik, useFormik } from "formik";
import { useContext, useEffect, useState } from "react";
import StateContext from "../state/StateContext";
interface LockerPanelFormValuesType {
  lock: boolean;
  block: boolean;
  status: string;
  name: string;
}

const initialValues: LockerPanelFormValuesType = {
  lock: false,
  block: false,
  status: "",
  name: "",
};

const LockerPanel = () => {
  const [isRenameMode, setIsRenameMode] = useState(false);
  const [renameField, setRenameField] = useState("");
  const { state } = useContext(StateContext);
  const formik = useFormik({
    initialValues: initialValues,
    onSubmit: async (values: LockerPanelFormValuesType) => {
      console.log(formik.values);
      if (state?.user?.admin) {
        const response = await fetch(
          `${process.env.REACT_APP_BACKEND}/lockers/${state.user?.locker_id}`,
          {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({
              username: state?.user?.name,
              password: state?.user?.password,
              locked: formik.values.lock,
              blocked: formik.values.block,
              status: formik.values.status ?? null,
              name: renameField === "" ? formik.values.name : renameField,
            }),
          }
        );
        const data = await response.json();
        if (response.ok) {
          formik.setValues({
            lock: data.locked,
            block: data.blocked,
            status: data.status,
            name: data.name,
          });
        }
        setRenameField("");
      }
    },
  });
  useEffect(() => {
    if (state?.user) {
      (async () => {
        const response = await fetch(
          `${process.env.REACT_APP_BACKEND}/lockers/${state.user?.locker_id}`
        );
        const data = await response.json();
        if (response.ok) {
          formik.setValues({
            lock: data.locked,
            block: data.blocked,
            status: data.status,
            name: data.name,
          });
        }
      })();
    }
  }, [state?.user]);

  return (
    <div className="mx-auto mt-[20vh] w-min">
      <form onSubmit={formik.handleSubmit}>
        {state?.user && (
          <div className="relative form-section p-3 h-20 rounded-2xl bg-slate-300 w-full mb-2 flex justify-between items-center">
            <div className="flex-grow text-center text-xl font-semibold">
              {formik.values.name}
            </div>
            <div className="absolute right-0 mr-5">
              <button
                type="button"
                className=" border-2 border-black p-3 w-28 hover:bg-yellow-400 rounded-lg bg-yellow-500 text-white font-bold"
                onClick={() => setIsRenameMode(!isRenameMode)}
              >
                {isRenameMode ? "Back" : "Rename"}
              </button>
            </div>
          </div>
        )}
        <div className="w-min p-3 rounded-2xl bg-slate-300">
          {isRenameMode ? (
            <div className="form-section">
              <label>New Name</label>
              <input
                className="mx-1 text-field"
                type="text"
                disabled={!state?.user}
                onChange={(e) => setRenameField(e.target.value)}
                value={renameField}
              />
            </div>
          ) : (
            <>
              <div className="form-section flex justify-between w-24">
                <label>Lock</label>
                <input
                  className="mx-1 h-5 w-5 my-auto"
                  type="checkbox"
                  name="lock"
                  disabled={!state?.user?.admin}
                  onChange={formik.handleChange}
                  checked={formik.values.lock}
                />
              </div>
              <div className="form-section flex justify-between w-24">
                <label>Block</label>
                <input
                  className="mx-1 h-5 w-5 my-auto"
                  type="checkbox"
                  name="block"
                  disabled={!state?.user?.admin}
                  onChange={formik.handleChange}
                  checked={formik.values.block}
                />
              </div>
              <div className="form-section">
                <label>Status</label>
                <input
                  className="mx-1 text-field"
                  type="text"
                  name="status"
                  disabled={!state?.user}
                  onChange={formik.handleChange}
                  value={formik.values.status}
                />
              </div>
            </>
          )}
          <div className="text-center">
            <button
              className="btn-submit"
              type="submit"
              disabled={!state?.user}
            >
              Submit
            </button>
          </div>
        </div>
      </form>
    </div>
  );
};
export default LockerPanel;
