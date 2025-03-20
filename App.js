import React, { useState, useEffect } from "react";
import { db } from "./firebaseConfig";
import { ref, set, onValue } from "firebase/database";

const App = () => {
  const [light1, setLight1] = useState(false);
  const [fan1, setFan1] = useState(false);

  useEffect(() => {
    const lightRef = ref(db, "/home/light1");
    const fanRef = ref(db, "/home/fan1");

    onValue(lightRef, (snapshot) => setLight1(snapshot.val()));
    onValue(fanRef, (snapshot) => setFan1(snapshot.val()));
  }, []);

  const toggleLight = () => set(ref(db, "/home/light1"), light1 ? 0 : 1);
  const toggleFan = () => set(ref(db, "/home/fan1"), fan1 ? 0 : 1);

  return (
    <div className="flex flex-col items-center mt-10">
      <h1 className="text-2xl font-bold">IoT Home Automation</h1>
      <button onClick={toggleLight} className="px-4 py-2 m-2 bg-blue-500 text-white rounded">
        Light: {light1 ? "ON" : "OFF"}
      </button>
      <button onClick={toggleFan} className="px-4 py-2 m-2 bg-green-500 text-white rounded">
        Fan: {fan1 ? "ON" : "OFF"}
      </button>
    </div>
  );
};

export default App;
