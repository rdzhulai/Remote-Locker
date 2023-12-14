import { ReactNode } from "react";

interface Props {
  children: ReactNode;
}
const NavBar = ({ children }: Props) => {
  return <nav className="flex justify-center my-1">{children}</nav>;
};

export default NavBar;
