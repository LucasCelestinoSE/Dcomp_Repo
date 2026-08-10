module cd4017 (
    input wire clk,       // Clock input 
    input wire rst,       // Reset
    input wire clk_en,    // Clock Enable
    output reg [9:0] q    // Output: 3, 2, 4, 7, 10, 1, 5, 6, 9, 11
);

always @(posedge clk or posedge rst) begin
    if (rst) begin
        q <= 10'b0000000001; // Reset
    end else if (!clk_en) begin
        if (q == 10'b1000000000) begin
            q <= 10'b0000000001; // Reset
        end else begin
            q <= q << 1;        // Shift
        end
    end
end

endmodule
