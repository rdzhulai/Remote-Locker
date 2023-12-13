import { useState } from "react";

const PasswordField = () => {
    const [password, setPassword] = useState("");
    const onSubmit = () => {
        //TODO
    };
    return (
        <>
            <div className="text-center mt-[20vh]">
                <form onSubmit={onSubmit}>
                    <input
                        className="rounded-lg p-3 w-[40vh] hover:bg-blue-200 border-2 border-black outline-none"
                        type="text"
                        value={password}
                        placeholder="Enter your password"
                        onChange={(e) => {
                            setPassword(e.target.value);
                        }}
                    ></input>
                    <input
                        className="border-2 border-black p-3 rounded-lg ml-2 bg-green-700 text-white font-bold"
                        type="submit"
                        value="Submit"
                    />
                </form>
            </div>
        </>
    );
};

export default PasswordField;
